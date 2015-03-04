#ifndef PATHNODE_H
#define PATHNODE_H

#include <QObject>
#include <QFileSystemWatcher>

class PathNode : public QObject
{
    Q_OBJECT
private:
    QString m_localPath;
    QString m_cloudPath;
    QMap<QString, QString> *m_properties;
    QFileSystemWatcher *m_watcher;

public:
    explicit PathNode(QObject *parent = 0);
    ~PathNode();

    QString localPath() const;
    void setLocalPath(const QString &value);

    QString cloudPath() const;
    void setCloudPath(const QString &value);

    QMap<QString, QString> *properties() const;
    void setProperties(QMap<QString, QString> *value);
    void insertProperty(const QString& key, const QString& value);

    void startWatching();
    void stopWatching();
signals:

public slots:
    void fileChanged(QString file);
    void directoryChanged(QString directory);
};

#endif // PATHNODE_H
