#ifndef CREATEAPPLICATIONDIALOG_H
#define CREATEAPPLICATIONDIALOG_H

#include "appdata.h"
#include "applicationpropertieslistmodel.h"

#include <QDialog>

namespace Ui {
class CreateApplicationDialog;
}

class CreateApplicationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateApplicationDialog(QWidget *parent = 0);
    ~CreateApplicationDialog();

private slots:
    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::CreateApplicationDialog *ui;
    AppData *m_AppData;
    ApplicationPropertiesListModel *model;
};

#endif // CREATEAPPLICATIONDIALOG_H
