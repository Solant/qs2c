#include <QDir>
#include <QFileDialog>

#include "settings.h"
#include "ui_settings.h"
#include "settingscontainer.h"
#include "xmlparser.h"

extern SettingsContainer settings;

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->firstLaunchLabel->setVisible(!ui->closeButton->isVisible());
    setWindowTitle("Settings");
    ui->cloudFolderLineEdit->setText(settings.cloudFolder());
    QFile cache(settings.cacheFolder() + "gameList");
    ui->cacheSizeLabel->setText(QString::number(cache.size()/1000) + " KB");
}

void Settings::showFirstLaunchDialog()
{
    ui->closeButton->setEnabled(false);
    ui->applyButton->setEnabled(false);
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
    settings.setCloudFolder(ui->cloudFolderLineEdit->text());
    XmlParser::writeSettings(settings.settingsMap());
    ui->closeButton->setEnabled(true);
    this->close();
}

void Settings::on_cloudFolderLineEdit_textChanged(const QString &arg1)
{
    if (QDir(arg1).exists() && !arg1.isEmpty())
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
    QFile cache(settings.cacheFolder() + "gameList");
    if(cache.exists()){
        cache.remove();
        ui->cacheSizeLabel->setText("0 KB");
    }
}
