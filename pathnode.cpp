#include <QMap>
#include "pathnode.h"

void PathNode::setPath(const QString &value)
{
    m_path = value;
}

QString PathNode::path() const
{
    return m_path;
}

QString PathNode::cloudPath() const
{
    return m_cloudPath;
}

void PathNode::setCloudPath(const QString &value)
{
    m_cloudPath = value;
}

QMap<QString, QString> *PathNode::properties() const
{
    return m_properties;
}

void PathNode::setProperties(QMap<QString, QString> *value)
{
    m_properties = value;
}

void PathNode::insertProperty(const QString &key, const QString &value)
{
    m_properties->insert(key, value);
}

void PathNode::fileChanged(QString file)
{
    //TODO connection to syncprovider
}
PathNode::PathNode(QObject *parent) : QObject(parent)
{

}

PathNode::~PathNode()
{
    if(m_properties)
        delete m_properties;
}

