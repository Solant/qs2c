#include "pcgamingwikidialog.h"
#include "ui_pcgamingwikidialog.h"

PcGamingWikiDialog::PcGamingWikiDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PcGamingWikiDialog)
{
    ui->setupUi(this);
    m_manager = new QNetworkAccessManager(this);
}

PcGamingWikiDialog::~PcGamingWikiDialog()
{
    delete ui;
    delete m_manager;
}

void PcGamingWikiDialog::replyFinished(QNetworkReply *reply)
{
    QByteArray d = reply->readAll();
    QString html(d);
    ui->updateButton->setEnabled(true);
    disconnect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    ui->progressBar->setValue(100);
}

void PcGamingWikiDialog::updateDatabase()
{
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    m_manager->get(QNetworkRequest(QUrl("http://pcgamingwiki.com/wiki/Category:Games")));
    ui->progressBar->setValue(0);
}

void PcGamingWikiDialog::on_updateButton_clicked()
{
   updateDatabase();
   ui->updateButton->setDisabled(true);
}
