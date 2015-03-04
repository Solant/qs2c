#include "applicationpropertiestablemodel.h"

ApplicationPropertiesTableModel::ApplicationPropertiesTableModel(AppData *app, QObject *parent) : QAbstractTableModel(parent)
{
    this->app = app;
}

int ApplicationPropertiesTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return app->pathNodes().size();
}

int ApplicationPropertiesTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant ApplicationPropertiesTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole){
        if(index.column() == 0)
            return app->pathNodes().at(index.row())->localPath();

        if(index.column() == 1)
            return app->pathNodes().at(index.row())->cloudPath();
    }
    return QVariant();
}

QVariant ApplicationPropertiesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Vertical)
        return QVariant();

    if (role != Qt::DisplayRole)
             return QVariant();

    switch (section) {
        case 0:
            return "Local file";

     case 1:
         return "Cloud storage file";

     default:
         return QVariant();
    }

    return QVariant();
}
