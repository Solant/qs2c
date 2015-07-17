#include <QDebug>

#include "mainwindowapplicationlistmodel.h"
#include "settingscontainer.h"

extern SettingsContainer settings;

MainWindowApplicationListModel::MainWindowApplicationListModel()
{
}

int MainWindowApplicationListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return settings.apps()->size();
}

QVariant MainWindowApplicationListModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && role == Qt::DisplayRole){
        if (settings.apps()->size() > index.row())
            return settings.apps()->at(index.row())->name();
    }
    return QVariant();
}

void MainWindowApplicationListModel::update()
{
    QVector<int> roles;
    for (int i = 0; i < settings.apps()->size(); i++)
        roles.append(Qt::DisplayRole);

    emit dataChanged(this->index(0), this->index(settings.apps()->size()), roles);
}
