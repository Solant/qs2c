#ifndef APPLICATIONPROPERTIESTABLEMODEL_H
#define APPLICATIONPROPERTIESTABLEMODEL_H

#include <QAbstractTableModel>

#include "appdata.h"

class ApplicationPropertiesTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ApplicationPropertiesTableModel(AppData app, QObject *parent = 0);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    AppData app;
};

#endif // APPLICATIONPROPERTIESTABLEMODEL_H
