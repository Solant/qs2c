#ifndef SETTINGSCONTAINER_H
#define SETTINGSCONTAINER_H

#include <QMap>

#include "appdata.h"

extern SettingsContainer settngs;

class SettingsContainer
{
private:
    QMap<QString, QString> m_settings;
    QList<AppData *> m_apps;
public:
    SettingsContainer();
    QString cacheFolder() const;
    void setCacheFolder(const QString &cacheFolder);
    QString settingsFolder() const;
    void setSettingsFolder(const QString &settingsFolder);
    QString cloudFolder() const;
    void setCloudFolder(const QString &cloudFolder);
    QList<AppData *> apps() const;
    void setApps(const QList<AppData *> &apps);
    void addApp(const AppData *app);
    void writeSettings();
    bool containsAppWithName(const QString &name);
};

#endif // SETTINGSCONTAINER_H
