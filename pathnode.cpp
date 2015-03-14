#include <QMap>
#include <QFileInfo>
#include <QDir>

#include "pathnode.h"
#include "syncprovider.h"

void PathNode::setLocalPath(const QString &value)
{
    m_localPath = value;
}

QString PathNode::localPath() const
{
    return m_localPath;
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

void PathNode::startWatching()
{
    m_watcher->addPath(m_localPath);
    m_watcher->addPath(m_cloudPath);
    SyncProvider::syncFiles(this->localPath(), this->cloudPath());
    if(QFileInfo(m_localPath).isFile())
        connect(m_watcher, SIGNAL(fileChanged(QString)),
                this, SLOT(fileChanged(QString)));
    else
        connect(m_watcher, SIGNAL(directoryChanged(QString)),
                this, SLOT(directoryChanged(QString)));
}

void PathNode::stopWatching()
{
    m_watcher->removePath(m_localPath);
    m_watcher->removePath(m_cloudPath);
}

void PathNode::fileChanged(QString file)
{
    stopWatching();
    SyncProvider::syncFiles(this->localPath(), this->cloudPath());
    m_watcher->addPath(this->localPath());
    m_watcher->addPath(this->cloudPath());
}

void PathNode::directoryChanged(QString directory)
{
    //TODO connection to syncprovider
}

PathNode::PathNode(QObject *parent) : QObject(parent)
{
    m_watcher = new QFileSystemWatcher();
    m_properties = new QMap<QString, QString>;
}

PathNode::~PathNode()
{
    if(m_properties)
        delete m_properties;

    if(m_watcher)
        delete m_watcher;
}

