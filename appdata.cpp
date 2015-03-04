#include "appdata.h"


QString AppData::fileName() const
{
    return m_fileName;
}

void AppData::setFileName(const QString &fileName)
{
    m_fileName = fileName;
}

QList<PathNode *> AppData::pathNodes() const
{
    return m_pathNodes;
}

void AppData::setPathNodes(const QList<PathNode *> &pathNodes)
{
    m_pathNodes = pathNodes;
}

void AppData::addPathNode(PathNode *pathNode)
{
    m_pathNodes.append(pathNode);
}

AppData::AppData()
{

}

AppData::~AppData()
{

}

QString AppData::name() const
{
    return m_name;
}

void AppData::setName(const QString &name)
{
    m_name = name;
}
