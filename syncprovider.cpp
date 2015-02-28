#include <QDir>
#include <QDebug>
#include <QFile>
#include <QDateTime>

#include "syncprovider.h"
#include "settingscontainer.h"
#include "settings.h"

SyncProvider::SyncProvider()
{
    m_Watcher = new QFileSystemWatcher();
    QObject::connect(m_Watcher, SIGNAL(fileChanged(QString)),
                     this, SLOT(fileChangeHandler(QString)));
    checkFolders();
}

SyncProvider::~SyncProvider()
{
   if(m_Watcher)
       delete m_Watcher;
}

void SyncProvider::deleteApp(int index)
{
    AppData* a = SettingsContainer::apps()->at(index);
    m_Watcher->removePaths(a->files());
    m_Watcher->removePaths(a->cloudFiles());
    QFile::remove(SettingsContainer::settingsFolder() + "prepared" + QDir::separator() + a->fileName());
    SettingsContainer::apps()->removeAt(index);
}

void SyncProvider::fileChangeHandler(QString file)
{
    qDebug() << "File " + file + " changed";
    m_Watcher->removePath(file);
    QString file2 = "";
    for(int i = 0; i < SettingsContainer::apps()->size(); i++){
        if(SettingsContainer::apps()->at(i)->cloudFiles().contains(file)){
            AppData* tmp =  SettingsContainer::apps()->at(i);
            file2 = tmp->files().at(SettingsContainer::apps()->at(i)->cloudFiles().indexOf(file));
            break;
        }
    }
    if(file2 == ""){
        for(int i = 0; i < SettingsContainer::apps()->size(); i++){
            if(SettingsContainer::apps()->at(i)->files().contains(file)){
                AppData* tmp =  SettingsContainer::apps()->at(i);
                file2 = tmp->cloudFiles().at(SettingsContainer::apps()->at(i)->files().indexOf(file));
                break;
            }
        }
    }
    m_Watcher->removePath(file2);
    syncFiles(file, file2);
    m_Watcher->addPath(file);
    m_Watcher->addPath(file2);
}

void SyncProvider::addApp(AppData* data)
{
    QDir appDir(settings.cloudFolder() + QDir::separator() + ".qs2c" + QDir().separator() + "apps" + QDir().separator() + data->name() + QDir::separator());
    if(!appDir.exists()){
        appDir.mkpath(appDir.path());
        for(PathNode* pathNode : data->pathNodes()){
            QFileInfo pathInfo(pathNode->path());
            if(pathInfo.isFile()){
                pathNode->setCloudPath(appDir.path() + pathInfo.fileName());
                QFile::copy(pathNode->path(), pathNode->cloudPath());
                m_Watcher->addPath(pathNode->path());
                m_Watcher->addPath(pathNode->cloudPath());
                connect(m_Watcher, SIGNAL(fileChanged(QString)),
                        pathNode, SLOT(fileChanged(QString)));
            }
            if(pathInfo.isDir()){
                //TODO dir copy
            }
        }
    } else{

    }
    settings.addApp(data);
//    QDir appDir(SettingsContainer::settings()->value("cloud-folder") + QDir::separator() + ".qs2c" + QDir().separator() + "apps" + QDir().separator() + data->name());
//    if(!appDir.exists()){
//        QDir().mkdir(appDir.absolutePath());
//        QStringList tmp;
//        for(int i = 0; i < data->files().size(); i++){
//            QFile::copy(data->files().at(i),
//                        appDir.absolutePath() + QDir::separator() + QFileInfo(data->files().at(i)).fileName());
//            tmp << appDir.absolutePath() + QDir::separator() + QFileInfo(data->files().at(i)).fileName();
//        }
//        data->setCloudFiles(tmp);
//    }
//    else{
//        QStringList cloudFiles;
//        for(int i = 0; i < data->files().size(); i++){
//            syncFiles(data->files().at(i),
//                      appDir.absolutePath() + QDir::separator() + QFileInfo(data->files().at(i)).fileName());
//            cloudFiles << appDir.absolutePath() + QDir::separator() + QFileInfo(data->files().at(i)).fileName();
//        }
//        data->setCloudFiles(cloudFiles);
//        SettingsContainer::addApp(data);
//    }
//    m_Watcher->addPaths(data->files());
//    m_Watcher->addPaths(data->cloudFiles());
}

void SyncProvider::syncFiles(QString file0, QString file1)
{
    QFileInfo a(file0);
    QFileInfo b(file1);

    if(a.exists() && b.exists()){
        if (a.lastModified() > b.lastModified()){
            if(QFile::remove(b.filePath()))
                qDebug() << "[LOG] File " + b.filePath() + " deleted";

            if(QFile::copy(a.filePath(), b.filePath()))
                qDebug() << "[LOG] File " + a.filePath() + " copied to " + b.filePath();
        }
        if (a.lastModified() < b.lastModified()){
            if(QFile::remove(a.filePath()))
                qDebug() << "[LOG] File " + a.filePath() + " deleted";

            if(QFile::copy(b.filePath(), a.filePath()))
                qDebug() << "[LOG] File " + b.filePath() + " copied to " + a.filePath();
        }
    }
    if(!a.exists())
        if(QFile::copy(b.filePath(), a.filePath()))
            qDebug() << "[LOG] File " + b.filePath() + " copied to " + a.filePath();

    if(!b.exists())
        if(QFile::copy(a.filePath(), b.filePath()))
            qDebug() << "[LOG] File " + a.filePath() + " copied to " + b.filePath();
}

void SyncProvider::checkFolders()
{
    if (!QDir(SettingsContainer::settingsFolder()).exists()){
        qDebug() << "[LOG] Folder " + SettingsContainer::settingsFolder() + " not found, creating";
        QDir().mkpath(SettingsContainer::settingsFolder());                         //Windows fix for standard path
        QDir().mkdir(SettingsContainer::settingsFolder() + "prepared");
        QDir().mkdir(SettingsContainer::settingsFolder() + "original");
    }

    if(!QDir(SettingsContainer::cacheFolder()).exists()){
        qDebug() << "[LOG] Folder " + SettingsContainer::cacheFolder() + " not found, creating";
        QDir().mkpath(SettingsContainer::cacheFolder());
    }

    QString cloud = SettingsContainer::settings()->value("cloud-folder");
    if (!QDir(cloud).exists()){
        Settings* settings = new Settings();
        settings->disableCancelButton();
        settings->exec();
    }

    if (!QDir(cloud + QDir::separator() + ".qs2c").exists()){
        QDir().mkdir(cloud + QDir::separator() + ".qs2c");
        QDir().mkdir(cloud + QDir::separator() + ".qs2c" + QDir::separator() + "shared");
        QDir().mkdir(cloud + QDir::separator() + ".qs2c" + QDir::separator() + "apps");
    }
}
