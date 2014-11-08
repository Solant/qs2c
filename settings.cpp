#include <QDir>
#include <QFileDialog>

#include "settings.h"
#include "ui_settings.h"
#include "settingscontainer.h"
#include "xmlparser.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->cloudFolderLineEdit->setText(SettingsContainer::settings()->find("cloud-folder").value());
}

void Settings::disableCancelButton()
{
    ui->closeButton->setEnabled(false);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_closeButton_clicked()
{
    this->close();
}

void Settings::on_applyButton_clicked()
{
    SettingsContainer::m_Map->insert("cloud-folder", ui->cloudFolderLineEdit->text());
    XMLParser xml;
    xml.writeSettings();
    ui->closeButton->setEnabled(true);
    this->close();
}

void Settings::on_cloudFolderLineEdit_textChanged(const QString &arg1)
{
    if (QDir(arg1).exists() && arg1 != "")
        ui->applyButton->setEnabled(true);
    else
        ui->applyButton->setEnabled(false);
}

void Settings::on_pushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->cloudFolderLineEdit->setText(dir);
}

void Settings::closeEvent(QCloseEvent *event)
{
    if (!ui->closeButton->isEnabled())
        exit(0);
}
