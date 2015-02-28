#ifndef PCGAMINGWIKIDIALOG_H
#define PCGAMINGWIKIDIALOG_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QCompleter>
#include <QStringListModel>

namespace Ui {
class PcGamingWikiDialog;
}

class PcGamingWikiDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PcGamingWikiDialog(QWidget *parent = 0);
    ~PcGamingWikiDialog();

public slots:
    void replyFinished(QNetworkReply*reply);
    void appPageLoaded(QNetworkReply *reply);

private slots:
    void on_updateButton_clicked();
    void on_selectButton_clicked();

private:
    Ui::PcGamingWikiDialog *ui;
    QNetworkAccessManager* m_manager;
    QCompleter *m_completer;
    QStringListModel *m_model;
    QPair<QStringList, QStringList> gamesListPair;
    void updateDatabase();
    void saveCachedList();
    void loadCachedList();
};

#endif // PCGAMINGWIKIDIALOG_H
