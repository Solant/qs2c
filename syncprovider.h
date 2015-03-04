#ifndef SYNCPROVIDER_H
#define SYNCPROVIDER_H

#include <QObject>
#include <QMap>
#include <QFileSystemWatcher>

#include "appdata.h"

class SyncProvider : public QObject
{

    Q_OBJECT

private:
    void syncFiles(QString file0, QString file1);
    void checkFolders();
public:
    SyncProvider();
    ~SyncProvider();
    void deleteApp(int index);
    void addApp(AppData *data);
};

#endif // SYNCPROVIDER_H
