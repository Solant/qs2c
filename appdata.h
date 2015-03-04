#ifndef APPDATA_H
#define APPDATA_H

#include <QString>
#include "pathnode.h"

class AppData
{
private:
    QString m_name;
    QString m_fileName;
    QList<PathNode*> m_pathNodes;
public:
    AppData();
    ~AppData();
    QString name() const;
    void setName(const QString &name);
    QString fileName() const;
    void setFileName(const QString &fileName);
    QList<PathNode*> pathNodes() const;
    void setPathNodes(const QList<PathNode*> &pathNodes);
    void addPathNode(PathNode *pathNode);
};

#endif // APPDATA_H
