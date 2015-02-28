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
    setWindowTitle("Settings");
    ui->cloudFolderLineEdit->setText(SettingsContainer::settings()->find("cloud-folder").value());
    QFile cache(SettingsContainer::cacheFolder() + "gameList");
    ui->cacheSizeLabel->setText(QString::number(cache.size()/1000) + " KB");
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
    SettingsContainer::setSettingValue("cloud-folder", ui->cloudFolderLineEdit->text());
    XmlParser xml;
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
    Q_UNUSED(event);
    if (!ui->closeButton->isEnabled())
        exit(0);
}

void Settings::on_cleanCacheButton_clicked()
{
    QFile cache(SettingsContainer::cacheFolder() + "gameList");
    if(cache.exists()){
        cache.remove();
        ui->cacheSizeLabel->setText("0 KB");
    }
}
