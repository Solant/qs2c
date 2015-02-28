#include <QFile>
#include <QDebug>
#include <QXmlStreamReader>
#include <QDir>
#include <QStandardPaths>
#include <QList>
#include <QXmlStreamWriter>
#include <QRegularExpression>

#include "xmlparser.h"
#include "settingscontainer.h"
#include "pathnode.h"

#ifdef Q_OS_WIN32
#define OS "Windows"
#endif

#ifdef Q_OS_LINUX
#define OS "Linux"
#endif

#ifdef Q_OS_OSX
#define OS "OS X"
#endif

XmlParser::XmlParser()
{

}

void XmlParser::writeSettings(QMap<QString, QString> *map)
{
    QFile* file = new QFile(SettingsContainer::settingsFolder() + "settings.xml");
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "[ERROR] Unable to open " + file->fileName();
        delete file;
    }

    QXmlStreamWriter xml(file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement("config");
    QStringList keys = map->keys();
    for(QString key : keys){
        xml.writeTextElement(key, map->value(key));
    }
    xml.writeEndElement();
    xml.writeEndDocument();
    file->close();
}

QMap<QString, QString> *XmlParser::readSettings()
{
    QFile* file = new QFile(SettingsContainer::settingsFolder() + "settings.xml");
    if (!file->exists()){
        delete file;
        QMap<QString, QString>* map = new QMap<QString, QString>();
        map->insert("cloud-folder", "none");
        return map;
    }

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "[ERROR] Unable to open settings.xml";
        delete file;
        return NULL;
    }

    QXmlStreamReader xml(file);
    QMap<QString, QString>* map = new QMap<QString, QString>();
    while (!xml.atEnd() && !xml.hasError()){
        xml.readNext();
        if (xml.name() != "config" && xml.isStartElement())
            map->insert(xml.name().toString(), xml.readElementText());
    }

    if(xml.hasError()){
        qDebug() << "[ERROR] Invalid " + file->fileName() + " file";
        delete file;
        return NULL;
    }

    delete file;
    return map;
}

void XmlParser::saveUnpreparedConfig(AppData *appData, QString &filePath)
{
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "[ERROR] Unable to open " + file.fileName();
        return;
    }

    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement("application");
    xml.writeTextElement("name", appData->name());
    xml.writeTextElement("os", OS);
    for (int i = 0; i < appData->files().size(); i++)
        xml.writeTextElement("file", appData->files().at(i));

    xml.writeEndElement();
    xml.writeEndDocument();
    qDebug() << "[LOG] File " + filePath + " created";
    file.close();//TODO create unrepared configuration
}


AppData* XmlParser::loadUnpreparedConfig(QString &filePath)
{
    QFile* file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "[ERROR] Unable to open " << filePath;
        delete file;
    }

    QXmlStreamReader xml(file);
    AppData* app = new AppData;
    app->setFileName(QFileInfo(filePath).fileName());
    while (!xml.atEnd() && !xml.hasError()){
        xml.readNext();
        if(xml.name() == "name" && xml.isStartElement())
            app->setName(xml.readElementText());

        if(xml.name() == "os" && xml.isStartElement()){
            if(OS == xml.attributes().value("type")){
                xml.readNextStartElement();
                while(xml.name() == "file"){
                    app->addFile(preparePath(xml.readElementText()));
                    xml.readNextStartElement();
                }
            }
            else
                xml.skipCurrentElement();
        }
    }

    if(xml.hasError()){
        qDebug() << "[ERROR] Error in xml file " << filePath << ": " << xml.errorString();
        delete file;
    }

    delete file;
    return app;
}

QPair<QStringList, QStringList> XmlParser::loadAppList(QString &page)
{
    QStringList titles;
    QStringList hrefs;

    QRegularExpression removeImTag("<img [a-zA-Z:\\/\"\\.= 0-9]+>");
    page.remove(removeImTag);
    page.remove(":");
    page.remove("async");
    QXmlStreamReader xml(page);
    while (!xml.atEnd() && !xml.hasError()){
        xml.readNext();
        if(xml.name() == "a" && xml.attributes().hasAttribute("href") && xml.attributes().hasAttribute("title")){
            titles.append(xml.attributes().value("title").toString());
            hrefs.append(xml.attributes().value("href").toString());
        }
    }
    if(xml.hasError()){
       qDebug() << "[ERROR] Error in responce page: " + xml.errorString()
                   + " Line: " + QString::number(xml.lineNumber());
    }
    QPair<QStringList, QStringList> pair(titles, hrefs);
    return pair;
}

QString XmlParser::loadAppConfigFromUrl(QString &page)
{
    QRegularExpression removeImTag("<img [a-zA-Z:\\/\"\\.= 0-9]+>");
    page.remove(removeImTag);
    page.remove(":");
    page.remove("async");
    QXmlStreamReader xml(page);
    while (!xml.atEnd() && !xml.hasError()){
        xml.readNext();
        while(xml.name() != "span" && xml.attributes().value("id") != "Save_game_data_location"){
            xml.readNext();
        }

        while(xml.name() != "span" && xml.attributes().value("id") != "Save_game_data_location"){
            xml.readNext();
        }
    }
    if(xml.hasError()){
       qDebug() << "[ERROR] Error in responce page: " + xml.errorString()
                   + " Line: " + QString::number(xml.lineNumber());
    }
    return "";
}

QString XmlParser::preparePath(QString filePath)
{
    QRegularExpression re("~");
    filePath.replace(re, QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0]);
    return filePath;
}

QStringList XmlParser::preparedConfigsPaths()
{
    QDir directory(QStandardPaths::standardLocations(QStandardPaths::ConfigLocation)[0] + QDir::separator() + "qs2c" + QDir::separator() + "prepared");
    QStringList filter;
    filter << "*.xml";
    QFileInfoList fileInfoList = directory.entryInfoList(filter, QDir::Files, QDir::Name);
    QStringList ret;
    for(int i = 0; i < fileInfoList.size(); i++)
        ret.append(fileInfoList.at(i).absoluteFilePath());

    return ret;
}

void XmlParser::savePreparedConfig(AppData *appData, QString &filePath)
{
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "[ERROR] Unable to open " + file.fileName();
        return;
    }

    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement("application");
    xml.writeTextElement("name", appData->name());
    for(PathNode pathNode : appData->pathNodes()){
        xml.writeStartElement("path");
        xml.writeAttribute("localpath", pathNode.path);
        xml.writeAttribute("cloudpath", pathNode.cloudPath);
        QStringList keys = pathNode.properties();
        xml.writeStartElement("properties");
        for(QString key : keys)
            xml.writeAttribute(key, pathNode.properties->value(key));
        xml.writeEndElement();
        xml.writeEndElement();
    }
    xml.writeEndElement();
    xml.writeEndDocument();
    qDebug() << "[LOG] File " + filePath + " created";
    file.close();
}

AppData* XmlParser::loadPreparedConfig(QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "[ERROR] Unable to open " << filePath;
        return NULL;
    }

    QXmlStreamReader xml(&file);
    AppData* app = new AppData;
    app->setFileName(QFileInfo(filePath).fileName());
    while (!xml.atEnd() && !xml.hasError()){
        xml.readNext();
        if(xml.name() == "name" && xml.isStartElement())
            app->setName(xml.readElementText());

        if(xml.name() == "path" && xml.isStartElement()){
            PathNode* pathNode = new PathNode;
            pathNode->setPath(xml.attributes().value("localpath"));
            pathNode->setCloudPath(xml.attributes().value("cloudpath"));
            while(xml.name() != "properties" && xml.isEndElement()){
                xml.readNext();
                pathNode->insertProperty(xml.name(), xml.readElementText());
            }
            app->addPathNode(pathNode);
        }
    }

    if(xml.hasError()){
        qDebug() << "[ERROR] Error in xml prepared xml file " << filePath << ": " << xml.errorString();
        delete app;
        return NULL;
    }

    return app;
}
