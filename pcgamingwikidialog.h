#ifndef PCGAMINGWIKIDIALOG_H
#define PCGAMINGWIKIDIALOG_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>

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

private slots:
    void on_updateButton_clicked();

private:
    Ui::PcGamingWikiDialog *ui;
    void updateDatabase();
    QNetworkAccessManager* m_manager;
};

#endif // PCGAMINGWIKIDIALOG_H
