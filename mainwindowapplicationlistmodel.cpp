#include <QDebug>

#include "mainwindowapplicationlistmodel.h"
#include "settingscontainer.h"

MainWindowApplicationListModel::MainWindowApplicationListModel()
{
}

int MainWindowApplicationListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return SettingsContainer::apps()->size();
}

QVariant MainWindowApplicationListModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && role == Qt::DisplayRole){
        if (SettingsContainer::apps()->size() > index.row())
            return SettingsContainer::apps()->at(index.row()).name();
    }
    return QVariant();
}

void MainWindowApplicationListModel::update()
{
    QVector<int> roles;
    for (int i = 0; i < SettingsContainer::apps()->size(); i++)
        roles.append(Qt::DisplayRole);

    emit dataChanged(this->index(0), this->index(SettingsContainer::apps()->size()), roles);
}
