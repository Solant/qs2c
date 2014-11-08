#include <QFile>
#include <QDebug>
#include <QXmlStreamReader>
#include <QDir>
#include <QStandardPaths>
#include <QList>
#include <QXmlStreamWriter>

#include "xmlparser.h"
#include "settingscontainer.h"

#ifdef Q_OS_WIN32
#define OS "Windows"
#endif

#ifdef Q_OS_LINUX
#define OS "Linux"
#endif

#ifdef Q_OS_OSX
#define OS "OS X"
#endif

XMLParser::XMLParser()
{

}

void XMLParser::writeSettings()
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
    xml.writeTextElement("cloud-folder", SettingsContainer::m_Map->value("cloud-folder"));
    xml.writeEndElement();
    xml.writeEndDocument();
    file->close();
}

void XMLParser::writeAppSettings(AppData *appData, QString filePath)
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
    file.close();
}

QMap<QString, QString> *XMLParser::readSettings()
{
    QFile* file = new QFile(QStandardPaths::standardLocations(QStandardPaths::ConfigLocation)[0]+"/qs2c/settings.xml");
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
        if (xml.name() == "cloud-folder")
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

AppData XMLParser::readAppSettings(QString filePath)
{
    QFile* file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "[ERROR] Unable to open " << filePath;
        delete file;
    }

    QXmlStreamReader xml(file);
    AppData app;
    app.setFileName(QFileInfo(filePath).fileName());
    while (!xml.atEnd() && !xml.hasError()){
        xml.readNext();
        if (xml.name() == "name" && xml.isStartElement()){
            app.setName(xml.readElementText());
        }

        if (xml.name() == "os" && xml.isStartElement()){
            app.setOS(xml.readElementText());
        }

        if(xml.name() == "file" && xml.isStartElement()){
            app.addFile(xml.readElementText());
        }
    }

    if(xml.hasError()){
        qDebug() << "[ERROR] Error in xml file " << filePath << ": " << xml.errorString();
        delete file;
    }

    delete file;
    return app;
}

QList<AppData> *XMLParser::readAppsSettings(QStringList files)
{
    QList<AppData>* apps = new QList<AppData>();
    for(int i = 0; i < files.size(); i++)
        apps->append(readAppSettings(files.at(i)));
    return apps;
}

QStringList XMLParser::preparedConfigsPaths()
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
