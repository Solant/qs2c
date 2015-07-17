#include <QDir>
#include <QDebug>
#include <QFile>
#include <QDateTime>

#include "syncprovider.h"
#include "settingscontainer.h"
#include "settings.h"

extern SettingsContainer settings;

SyncProvider::SyncProvider()
{
    checkFolders();
}

SyncProvider::~SyncProvider()
{
}

void SyncProvider::deleteApp(int index)
{
    AppData* a = settings.apps().at(index);
    QFile::remove(settings.settingsFolder() + "prepared" + QDir::separator() + a->fileName());
    settings.apps().removeAt(index);
}

void SyncProvider::addApp(AppData* data)
{
    QDir appDir(settings.cloudFolder() + QDir::separator() + ".qs2c" + QDir().separator() + "apps" + QDir().separator() + data->name() + QDir::separator());
    if(!appDir.exists())
        appDir.mkpath(appDir.path());

    for(PathNode* pathNode : data->pathNodes()){
        QFileInfo localPathInfo(pathNode->localPath());
        if(localPathInfo.isDir() && !localPathInfo.exists())
            appDir.mkpath(pathNode->localPath());

        if(pathNode->cloudPath().isEmpty()){
            QString cloudPath(settings.cloudFolder() + QDir::separator()
                              + ".qs2c" + QDir::separator() + "apps" + QDir::separator() + data->name() + QDir::separator());
            if(!QDir(cloudPath).exists())
                appDir.mkpath(cloudPath);

            if(!QFileInfo(cloudPath + localPathInfo.fileName()).exists() && QFileInfo(cloudPath + localPathInfo.fileName()).isDir())
                appDir.mkpath(cloudPath + localPathInfo.fileName());

        pathNode->setCloudPath(cloudPath + localPathInfo.fileName());
        }

        pathNode->startWatching();
    }
    settings.addApp(data);
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
    if(!QDir(settings.cacheFolder()).exists()){
        qDebug() << "[LOG] Folder " + settings.cacheFolder() + " not found, creating";
        QDir().mkpath(settings.cacheFolder());
    }

    if(!QDir(settings.settingsFolder()).exists()){
        qDebug() << "[LOG] Folder " + settings.settingsFolder() + " not found, creating";
        QDir().mkpath(settings.settingsFolder() + "prepared");
    }

    QString cloud = settings.cloudFolder();
    if (!QDir(cloud).exists() || cloud.isEmpty()){
        Settings* settings = new Settings();
        settings->showFirstLaunchDialog();
        settings->exec();
    }

    if (!QDir(cloud + QDir::separator() + ".qs2c").exists()){
        QDir().mkpath(cloud + ".qs2c" + QDir::separator() + "shared");
        QDir().mkdir(cloud + QDir::separator() + ".qs2c" + QDir::separator() + "apps");
    }
}
