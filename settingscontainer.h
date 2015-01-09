#ifndef SETTINGSCONTAINER_H
#define SETTINGSCONTAINER_H

#include <QMap>
#include <QList>

#include "appdata.h"

class SettingsContainer
{
private:
    static QMap<QString, QString>* m_Map;
    static QList<AppData>* m_Apps;
    static QString m_SettingsFolder;
public:
    static QMap<QString, QString> *settings();
    static QList<AppData>* apps();
    static void addApp(AppData app);
    static QString settingsFolder();
    static QString settingValue(const QString &key);
    static void setSettingValue(const QString &key, const QString &value);
};

#endif // SETTINGSCONTAINER_H
