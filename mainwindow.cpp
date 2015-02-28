#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
//#include <QStandardPaths>
#include <QCloseEvent>

#include "xmlparser.h"
#include "settings.h"
#include "settingscontainer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "applicationproperties.h"
#include "createapplicationdialog.h"
#include "pcgamingwikidialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/res/icon.png"));

    sync = new SyncProvider();
    trayIcon = new QSystemTrayIcon(QIcon(":/res/icon.png"));


    model = new MainWindowApplicationListModel();
    ui->listView->setModel(model);
    ui->listView->installEventFilter(this);
    QObject::connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                    this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

    //Right click Menu
    actionDelete = new QAction("Delete", this);
    actionProperties = new QAction("Properties", this);
    connect(actionDelete, SIGNAL(triggered()),
            this, SLOT(actionDelete_triggered()));
    connect(actionProperties, SIGNAL(triggered()),
            this, SLOT(actionProperties_triggered()));
    QList<QAction*> actions;
    actions.append(actionDelete);
    actions.append(actionProperties);
    rightClickMenu = new QMenu();
    rightClickMenu->addActions(actions);

    startUp();
}

MainWindow::~MainWindow()
{
    delete sync;
    delete ui;
    delete model;
    delete trayIcon;
    delete rightClickMenu;
//    SettingsContainer::clear(); TODO fix memory clean
}

void MainWindow::on_actionAdd_from_file_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("OpenFile"), "", tr("Application Preferences (*.xml)"));
    if(filePath == "")
        return;

//    QFile::copy(filePath,
//                SettingsContainer::settingsFolder() + "prepared" + QDir::separator() + QFileInfo(filePath).fileName());
    AppData* app = parser->loadUnpreparedConfig(filePath);

    if(settings.containsAppWithName(app->name())){
        QMessageBox::warning(this, "Warning", "Application with this name already exists");
        return;
    }

    sync->addApp(app);
    model->update();
}

void MainWindow::on_actionSettings_triggered()
{
    Settings *settings = new Settings(this);
    settings->exec();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About qs2c"),
                       tr("<p>qs2c is simple application for synchronization application data over cloud service.</p>"));
}

void MainWindow::startUp()
{
    QStringList filePaths = parser->preparedConfigsPaths();
    for(QString filePath : filePaths)
        sync->addApp(parser->loadPreparedConfig(filePath));

    model->update();
}

void MainWindow::on_actionCreateNew_triggered()
{
    CreateApplicationDialog app(this);
    app.exec();
}

void MainWindow::on_actionExit_triggered()
{
    SettingsContainer::clear();
    QCoreApplication::quit();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    on_actionMimimizeToTray_triggered();
    event->ignore();
}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::Trigger){
        trayIcon->hide();
        this->show();
    }
}

void MainWindow::on_actionMimimizeToTray_triggered()
{
    this->hide();
    trayIcon->show();
    trayIcon->setToolTip("qs2c is running in background");
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    Q_UNUSED(object);

    if(event->type() == QEvent::ContextMenu){
        QContextMenuEvent *menuEvent = dynamic_cast<QContextMenuEvent*>(event);
        rightClickMenu->exec(menuEvent->globalPos());
        return true;
    }

    return false;
}

void MainWindow::actionDelete_triggered()
{
    if(ui->listView->selectionModel()->selectedIndexes().size() != 1)
        return;

    int selected = ui->listView->selectionModel()->selectedIndexes().at(0).row();
    int answer = QMessageBox::question(this, "Confirm Dialog", "Are you sure?", QMessageBox::Yes, QMessageBox::No);
    if(answer == QMessageBox::Yes){
        sync->deleteApp(selected);
        model->update();
    }
}

void MainWindow::actionProperties_triggered()
{
    if(ui->listView->selectionModel()->selectedIndexes().size() != 1)
        return;

    int selected = ui->listView->selectionModel()->selectedIndexes().at(0).row();
    ApplicationProperties ap(SettingsContainer::apps()->at(selected), this);
    ap.exec();
}

void MainWindow::on_actionAdd_from_pcgamingwiki_triggered()
{
   PcGamingWikiDialog pgwd;
   pgwd.exec();
}
