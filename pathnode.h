#ifndef PATHNODE_H
#define PATHNODE_H

#include <QObject>

class PathNode : public QObject
{
    Q_OBJECT
private:
    QString m_path;
    QString cloudPath;
    QMap<QString, QString> *properties;

public:
    explicit PathNode(QObject *parent = 0);
    ~PathNode();

    QString path() const;
    void setPath(const QString &value);

    QString cloudPath() const;
    void setCloudPath(const QString &value);

    QMap<QString, QString> *properties() const;
    void setProperties(QMap<QString, QString> *value);
    void insertProperty(const QString& key, const QString& value);

signals:

public slots:
    void fileChanged(QString file);
};

#endif // PATHNODE_H
