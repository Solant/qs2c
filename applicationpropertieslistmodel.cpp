#include "applicationpropertieslistmodel.h"

ApplicationPropertiesListModel::ApplicationPropertiesListModel(AppData *app)
{
    m_AppData = app;
}

int ApplicationPropertiesListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_AppData->files().size();
}

QVariant ApplicationPropertiesListModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && role == Qt::DisplayRole){
        if (m_AppData->files().size() > index.row())
            return m_AppData->files().at(index.row());
    }
    return QVariant();
}

void ApplicationPropertiesListModel::addFile(const QString file)
{
    m_AppData->addFile(file);
    QVector<int> roles;
    for (int i = 0; i < m_AppData->files().size(); i++)
        roles.append(Qt::DisplayRole);

    emit dataChanged(this->index(0), this->index(m_AppData->files().size()), roles);
}

void ApplicationPropertiesListModel::removeFiles(QModelIndexList list)
{
    for(int i = 0; i < list.size(); i++){
        m_AppData->removeAt(list.at(i).row());
    }

    QVector<int> roles;
    for (int i = 0; i < m_AppData->files().size(); i++)
        roles.append(Qt::DisplayRole);

    emit dataChanged(this->index(0), this->index(m_AppData->files().size()), roles);
}
