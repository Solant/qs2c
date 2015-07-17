#ifndef SETTINGSCONTAINER_H
#define SETTINGSCONTAINER_H

#include <QMap>

#include "appdata.h"

class SettingsContainer
{
private:
    QMap<QString, QString>* m_settings;
    QList<AppData *>* m_apps;
public:
    SettingsContainer();
    QString cacheFolder() const;
    void setCacheFolder(const QString &cacheFolder);
    QString settingsFolder() const;
    void setSettingsFolder(const QString &settingsFolder);
    QString cloudFolder() const;
    void setCloudFolder(const QString cloudFolder);
    QList<AppData *> *apps() const;
    void setApps(QList<AppData *> *apps);
    void addApp(AppData *app);
    void removeApp(int index);
    void writeSettings();
    bool containsAppWithName(const QString &name);
    QMap<QString, QString> *settingsMap();
    QString preparedConfigFolder() const;

signals:
    void appAdded(AppData*);
};


#endif // SETTINGSCONTAINER_H
