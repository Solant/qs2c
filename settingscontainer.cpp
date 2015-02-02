#include <QDir>
#include <QStandardPaths>

#include "settingscontainer.h"
#include "xmlparser.h"

QMap<QString, QString>* SettingsContainer::m_Map = NULL;
QList<AppData*>* SettingsContainer::m_Apps = NULL;
QString SettingsContainer::m_SettingsFolder = "";

QMap<QString, QString>* SettingsContainer::settings()
{
    XmlParser* parser = new XmlParser();
    if(!m_Map)
        m_Map = parser->readSettings();

    delete parser;
    return m_Map;
}

QList<AppData*>* SettingsContainer::apps()
{
    if(!m_Apps)
        m_Apps = new QList<AppData*>();

    return m_Apps;
}

void SettingsContainer::addApp(AppData* app)
{
    if(!m_Apps)
        m_Apps = new QList<AppData*>();

    m_Apps->append(app);
}

QString SettingsContainer::settingsFolder()
{
    if(m_SettingsFolder == "")
        m_SettingsFolder = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation)[0] + QDir::separator() + "qs2c" + QDir::separator();

    return m_SettingsFolder;
}

QString SettingsContainer::settingValue(const QString &key)
{
    return m_Map->value(key);
}

void SettingsContainer::setSettingValue(const QString &key, const QString &value)
{
    m_Map->insert(key, value);
}

void SettingsContainer::clear()
{
    if(m_Map)
        delete m_Map;
    if(m_Apps)
        delete m_Apps;
}
