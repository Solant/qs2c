#include <QFileDialog>

#include "createapplicationdialog.h"
#include "ui_createapplicationdialog.h"
#include "xmlparser.h"

CreateApplicationDialog::CreateApplicationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateApplicationDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("New App Config");
    m_AppData = new AppData();
    model = new ApplicationPropertiesListModel(m_AppData);
    ui->listView->setModel(model);
    ui->listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

CreateApplicationDialog::~CreateApplicationDialog()
{
    delete ui;
}

void CreateApplicationDialog::on_addButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Select File", "", tr("Any file (*.*)"));
    if(file != "")
        model->addFile(file);
}

void CreateApplicationDialog::on_deleteButton_clicked()
{
    model->removeFiles(ui->listView->selectionModel()->selectedIndexes());
}

void CreateApplicationDialog::on_saveButton_clicked()
{
    m_AppData->setName(ui->nameEdit->text());
    QString filePath = QFileDialog::getSaveFileName(this, "Select File", "", tr("Application Settings (*.xml)"));
    if(filePath == "")
        return;

    if (!filePath.endsWith(".xml"))
        filePath.append(".xml");

    XmlParser xml;
    xml.writeAppSettings(m_AppData, filePath);
    this->close();
}
