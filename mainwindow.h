#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

#include "xmlparser.h"
#include "syncprovider.h"
#include "mainwindowapplicationlistmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionCreateNew_triggered();
    void on_actionAdd_from_file_triggered();
    void on_actionSettings_triggered();
    void on_actionAbout_triggered();
    void on_actionExit_triggered();
    void on_actionMimimizeToTray_triggered();
    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject *object, QEvent *event);

    void actionDelete_triggered();
    void actionProperties_triggered();
    void on_actionAdd_from_pcgamingwiki_triggered();

private:
    Ui::MainWindow *ui;
    XmlParser *parser;
    SyncProvider *sync;
    QSystemTrayIcon *trayIcon;
    MainWindowApplicationListModel *model;
    QAction* actionDelete;
    QAction* actionProperties;
    QMenu* rightClickMenu;
    void startUp();

public slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);

signals:
    void appAdded(AppData);
};

#endif // MAINWINDOW_H
