#include <QMessageBox>
#include <QStringListModel>
#include <QTimer>

#include "pcgamingwikidialog.h"
#include "ui_pcgamingwikidialog.h"
#include "xmlparser.h"

PcGamingWikiDialog::PcGamingWikiDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PcGamingWikiDialog)
{
    //UI setup
    ui->setupUi(this);
    ui->progressBar->setVisible(false);

    m_manager = new QNetworkAccessManager(this);

    //Dynamic completer model
    m_model = new QStringListModel();
    m_completer = new QCompleter(this);
    m_completer->setCaseSensitivity(Qt::CaseInsensitive);
    m_completer->setModel(m_model);
    ui->searchLineEdit->setCompleter(m_completer);
}

PcGamingWikiDialog::~PcGamingWikiDialog()
{
    delete ui;
    delete m_manager;
    delete m_completer;
    delete m_model;
}

void PcGamingWikiDialog::replyFinished(QNetworkReply *reply)
{
    QByteArray d = reply->readAll();
    QString html(d);
    disconnect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    ui->progressBar->setValue(100);
    QTimer::singleShot(1000, ui->progressBar, SLOT(hide()));
    gamesListPair = XmlParser::loadAppList(html);

    QString labelText = ui->label->text();
    labelText.replace(QRegularExpression("[0-9]+"), QString::number(gamesListPair.first.size()));
    labelText.replace(QRegularExpression(",[a-z ]+\\."), ".");
    ui->label->setText(labelText);
    m_model->setStringList(gamesListPair.first);
}

void PcGamingWikiDialog::appPageLoaded(QNetworkReply *reply)
{
    QByteArray d = reply->readAll();
    QString html(d);
    disconnect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(appPageLoaded(QNetworkReply*)));
    QString appConf = XmlParser::loadAppConfigFromUrl(html);
}

void PcGamingWikiDialog::updateDatabase()
{
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    m_manager->get(QNetworkRequest(QUrl("http://pcgamingwiki.com/wiki/Category:Games")));
    ui->progressBar->setValue(0);
    ui->progressBar->setVisible(true);
}

void PcGamingWikiDialog::on_updateButton_clicked()
{
   updateDatabase();
}

void PcGamingWikiDialog::on_selectButton_clicked()
{
    if(!gamesListPair.first.contains(ui->searchLineEdit->text())){
        QMessageBox::warning(this, "Game not found", "Game " + ui->searchLineEdit->text() + " not found in database");
    }
    else {
        connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(appPageLoaded(QNetworkReply*)));
        QString appPath = gamesListPair.second.at(gamesListPair.first.indexOf(ui->searchLineEdit->text()));
        m_manager->get(QNetworkRequest(QUrl("http://pcgamingwiki.com" + appPath)));
    }
}
