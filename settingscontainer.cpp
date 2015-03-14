#include <QDir>
#include <QStandardPaths>

#include "settingscontainer.h"
#include "xmlparser.h"

SettingsContainer settings;

QString SettingsContainer::settingsFolder() const
{
    return QStandardPaths::standardLocations(QStandardPaths::ConfigLocation)[0] + QDir::separator() + "qs2c" + QDir::separator();
}

QString SettingsContainer::preparedConfigFolder() const
{
    return settingsFolder() + "prepared" + QDir::separator();
}

void SettingsContainer::setSettingsFolder(const QString &settingsFolder)
{
    m_settings->insert("settings-folder", settingsFolder);
}

QString SettingsContainer::cloudFolder() const
{
    return m_settings->value("cloud-folder", "");
}

void SettingsContainer::setCloudFolder(const QString cloudFolder)
{
    m_settings->insert("cloud-folder", cloudFolder);
}

QList<AppData*> SettingsContainer::apps() const
{
    return m_apps;
}

void SettingsContainer::setApps(const QList<AppData*> &apps)
{
    m_apps = apps;
}

void SettingsContainer::addApp(AppData *app)
{
    m_apps.append(app);
    XmlParser::savePreparedConfig(app, preparedConfigFolder() + app->name() + ".xml");
}

void SettingsContainer::writeSettings()
{
    XmlParser::writeSettings(m_settings);
}

bool SettingsContainer::containsAppWithName(const QString &name)
{
    for(int i = 0; i < m_apps.size(); i++)
        if(m_apps.at(i)->name() == name)
            return true;

    return false;
}

QMap<QString, QString> *SettingsContainer::settingsMap()
{
    return m_settings;
}

SettingsContainer::SettingsContainer()
{
    m_settings = XmlParser::readSettings();
}

QString SettingsContainer::cacheFolder() const
{
    QString folder = m_settings->value("cache-folder", "");
    if(folder.isEmpty())
        return QStandardPaths::standardLocations(QStandardPaths::CacheLocation)[0] + QDir::separator() + "qs2c" + QDir::separator();

    return folder;
}

void SettingsContainer::setCacheFolder(const QString &cacheFolder)
{
    m_settings->insert("cache-folder", cacheFolder);
}
