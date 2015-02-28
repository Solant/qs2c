#include <QFile>
#include <QMessageBox>
#include <QStringListModel>
#include <QTimer>

#include "pcgamingwikidialog.h"
#include "ui_pcgamingwikidialog.h"
#include "xmlparser.h"
#include "settingscontainer.h"

PcGamingWikiDialog::PcGamingWikiDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PcGamingWikiDialog)
{
    //UI setup
    ui->setupUi(this);
    ui->progressBar->setVisible(false);

    loadCachedList();
    QString labelText = ui->label->text();
    labelText.replace(QRegularExpression("[0-9]+"), QString::number(gamesListPair.first.size()));
    if(gamesListPair.first.size())
        labelText.replace(QRegularExpression(",[a-z ]+\\."), ".");
    ui->label->setText(labelText);

    m_manager = new QNetworkAccessManager(this);

    //Dynamic completer model
    m_model = new QStringListModel(gamesListPair.first);
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
    disconnect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    QTimer::singleShot(1000, ui->progressBar, SLOT(hide()));
    if(reply->error() != QNetworkReply::NoError){
        QMessageBox::warning(this, "Network error", reply->errorString());
        return;
    }
    QByteArray d = reply->readAll();
    QString html(d);
    ui->progressBar->setValue(100);
    gamesListPair = XmlParser::loadAppList(html);

    QString labelText = ui->label->text();
    labelText.replace(QRegularExpression("[0-9]+"), QString::number(gamesListPair.first.size()));
    labelText.replace(QRegularExpression(",[a-z ]+\\."), ".");
    ui->label->setText(labelText);
    m_model->setStringList(gamesListPair.first);
    saveCachedList();
}

void PcGamingWikiDialog::appPageLoaded(QNetworkReply *reply)
{
    disconnect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(appPageLoaded(QNetworkReply*)));
    if(reply->error() != QNetworkReply::NoError){
        QMessageBox::warning(this, "Network error", reply->errorString());
        return;
    }
    QByteArray d = reply->readAll();
    QString html(d);
    QString appConf = XmlParser::loadAppConfigFromUrl(html);
}

void PcGamingWikiDialog::updateDatabase()
{
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    m_manager->get(QNetworkRequest(QUrl("http://pcgamingwiki.com/wiki/Category:Games")));
    ui->progressBar->setValue(0);
    ui->progressBar->setVisible(true);
}

void PcGamingWikiDialog::saveCachedList()
{
    QString fileName = SettingsContainer::cacheFolder() + "gameList";
    QFile cache(fileName);
    if(!cache.open(QIODevice::WriteOnly)){
        return;
    }
    QDataStream out(&cache);
    out << gamesListPair.first;
    out << gamesListPair.second;
    cache.close();
}

void PcGamingWikiDialog::loadCachedList()
{
    QString fileName = SettingsContainer::cacheFolder() + "gameList";
    QFile cache(fileName);
    if(!cache.exists())
        return;

    if(!cache.open(QIODevice::ReadOnly)){
        return;
    }
    QDataStream in(&cache);
    in >> gamesListPair.first;
    in >> gamesListPair.second;
    cache.close();
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
