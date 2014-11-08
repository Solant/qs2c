#ifndef MAINWINDOWAPPLICATIONLISTMODEL_H
#define MAINWINDOWAPPLICATIONLISTMODEL_H

#include <QAbstractListModel>

class MainWindowApplicationListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    MainWindowApplicationListModel();

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void update();
};

#endif // MAINWINDOWAPPLICATIONLISTMODEL_H
