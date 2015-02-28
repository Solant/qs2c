#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    void disableCancelButton();
    ~Settings();

private slots:
    void on_closeButton_clicked();
    void on_applyButton_clicked();
    void on_cloudFolderLineEdit_textChanged(const QString &arg1);
    void on_pushButton_clicked();
    void closeEvent(QCloseEvent *event);

    void on_cleanCacheButton_clicked();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
