#include "../include/Mainwindow/mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QKeyEvent>
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitWindowParameters();
    InitPrivateParameters();
}

MainWindow::~MainWindow()
{
    delete sysTray;
    delete config;
    delete ui;
}

void MainWindow::InitWindowParameters()
{
    setWindowTitle(tr("Актуалочка"));
    setFixedSize(QSize(640, 480));

    ui->tabWidget->setTabText(0, tr("Информация"));
    ui->tabWidget->setTabText(1, tr("Настройки"));
    ui->tabWidget->setTabText(2, tr("Календарь"));
    ui->tabWidget->setCurrentIndex(0);
    ui->labelVersion->setText(act::CurrnetVersion);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        close();
}

void MainWindow::InitPrivateParameters()
{
    config = new ConfigerExplorer(this);
    config->OpenJsonConfig();

    sysTray = new USystemTray(this);
    timer = new UTimerHandler(config->GetInterval());
    web = new UWebHandler(this);

    SetUpSettingsTab();
    SetUpConnects();

    QString url = "https://mpei-server.herokuapp.com/api/getSchedule";
    web->AccsessUrl(url);

}

void MainWindow::SetUpSettingsTab()
{
    ui->checkBoxAutoRun->setChecked(config->isAutoRunEnabled());
    ui->radioButtonNotify->setChecked(config->isNotifyEnabled());
    ui->spinBoxInterval->setValue(config->GetInterval() / act::oneHour);
    ui->spinBoxInterval->setReadOnly(!config->isNotifyEnabled());
}

void MainWindow::SetUpConnects()
{
    connect(sysTray->GetSettingsAction(), &QAction::triggered, this, [&]()
    {
        ui->tabWidget->setCurrentIndex(1);
        show();
    });

    connect(sysTray->GetCalendarAction(), &QAction::triggered, this, [&]()
    {
        ui->tabWidget->setCurrentIndex(2);
        show();
    });

    connect(sysTray->GetExitAction(), &QAction::triggered, this, [&]()
    {
        emit quitapp();
    });
}
