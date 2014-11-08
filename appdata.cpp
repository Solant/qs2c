#include "appdata.h"

void AppData::setFileName(const QString &fileName)
{
    m_FileName = fileName;
}

QStringList AppData::cloudFiles() const
{
    return m_CloudFiles;
}

void AppData::setCloudFiles(const QStringList &CloudFiles)
{
    m_CloudFiles = CloudFiles;
}

QString AppData::oS() const
{
    return m_OS;
}

void AppData::setOS(const QString &OS)
{
    m_OS = OS;
}
AppData::AppData()
{
    m_Name = "Unset";
}

AppData::~AppData()
{
}

QStringList AppData::files() const
{
    return m_Files;
}

void AppData::addFile(const QString file)
{
    m_Files.append(file);
}

void AppData::removeAt(int index)
{
    m_Files.removeAt(index);
}

QString AppData::name() const
{
    return m_Name;
}

void AppData::setName(const QString name)
{
    m_Name = name;
}

QString AppData::fileName() const
{
    return m_FileName;
}
