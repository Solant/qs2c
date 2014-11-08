#ifndef SETTINGSCONTAINER_H
#define SETTINGSCONTAINER_H

#include <QMap>
#include <QList>

#include "appdata.h"

class SettingsContainer
{
public:
    static QMap<QString, QString>* m_Map;
    static QList<AppData>* m_Apps;
    static QString m_SettingsFolder;
public:
    static QMap<QString, QString> *settings();
    static QList<AppData>* apps();
    static void addApp(AppData app);
    static QString settingsFolder();
};

#endif // SETTINGSCONTAINER_H
