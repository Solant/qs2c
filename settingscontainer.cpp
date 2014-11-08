#include <QDir>
#include <QStandardPaths>

#include "settingscontainer.h"
#include "xmlparser.h"

QMap<QString, QString>* SettingsContainer::m_Map = NULL;
QList<AppData>* SettingsContainer::m_Apps = NULL;
QString SettingsContainer::m_SettingsFolder = "";

QMap<QString, QString>* SettingsContainer::settings()
{
    XMLParser* parser = new XMLParser();
    if(!m_Map)
        m_Map = parser->readSettings();

    delete parser;
    return m_Map;
}

QList<AppData> *SettingsContainer::apps()
{
    if(!m_Apps){
        XMLParser parser;
        m_Apps = parser.readAppsSettings(parser.preparedConfigsPaths());
    }
    return m_Apps;
}

void SettingsContainer::addApp(AppData app)
{
    if(!m_Apps)
        m_Apps = new QList<AppData>();

    m_Apps->append(app);
}

QString SettingsContainer::settingsFolder()
{
    if(m_SettingsFolder == "")
        m_SettingsFolder = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation)[0] + QDir::separator() + "qs2c" + QDir::separator();

    return m_SettingsFolder;
}
