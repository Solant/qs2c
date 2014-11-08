#ifndef APPLICATIONPROPERTIESLISTMODEL_H
#define APPLICATIONPROPERTIESLISTMODEL_H

#include <QAbstractListModel>

#include "appdata.h"

class ApplicationPropertiesListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ApplicationPropertiesListModel(AppData *app);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void addFile(const QString file);
    void removeFiles(QModelIndexList list);
private:
    AppData* m_AppData;
};

#endif // APPLICATIONPROPERTIESLISTMODEL_H
