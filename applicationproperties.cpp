#include "applicationproperties.h"
#include "ui_applicationproperties.h"
#include "applicationpropertiestablemodel.h"

#include <QDebug>

ApplicationProperties::ApplicationProperties(AppData appData, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApplicationProperties)
{
    ui->setupUi(this);
    this->app = appData;
    this->setWindowTitle(app.name() + " properties");
    ui->applicationNameEdit->setText(app.name());

    model = new ApplicationPropertiesTableModel(appData);
    ui->tableView->setModel(model);

    for (int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c){
        ui->tableView->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
}

ApplicationProperties::~ApplicationProperties()
{
    delete ui;
    delete model;
}
