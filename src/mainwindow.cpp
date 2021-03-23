#include "../include/Mainwindow/mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QThread>
#include <QCheckBox>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Актуалочка");
    setFixedSize(QSize(640, 480));

    SetUpSystemTrayIcon();
    SetUpConfig();
    SetUpTimer();

    connect(ui->UpdateButton, &QPushButton::clicked, this, &MainWindow::notifyWithOutTray);
}

MainWindow::~MainWindow()
{
    config->WriteJson(config->GetJson());

    delete tIcon;
    delete timer;
    delete config;
    delete ui;
}

void MainWindow::InitParams()
{
    auto time = ((config->GetInterval() / 1000)/ 60) / 60;
    if (ui->spinBox)
        ui->spinBox->setValue(time);

    bool isChecked = config->isAutoRunEnable();
    if (ui->checkBox)
        ui->checkBox->setChecked(isChecked);
}

void MainWindow::onActivated(QSystemTrayIcon::ActivationReason reason)
{
    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);

    if (reason == QSystemTrayIcon::Unknown)
    {
        tIcon->showMessage(QString("Актуалочка"), content, icon, 1000000);
        ui->textEdit->setText(content);
    }
    else if (reason == QSystemTrayIcon::Trigger)
    {
        this->show();
        InitParams();
    }
}

void MainWindow::MessageClicked()
{
    this->show();
    InitParams();
}


void MainWindow::onResult(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QString strReply = (QString)reply->readAll();

        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();

        content = jsonObject["actuality"].toObject()["content"].toString();

        tIcon->setVisible(true);
        this->onActivated(QSystemTrayIcon::Unknown);
    }
    else
    {
        qDebug() << "ERROR";
    }
}

void MainWindow::onResultWithOutTray(QNetworkReply *reply)
{
    QString strReply = (QString)reply->readAll();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();

    content = jsonObject["actuality"].toObject()["content"].toString();

    ui->textEdit->setText(content);
}

void MainWindow::notify()
{
    QNetworkAccessManager* nam = new QNetworkAccessManager(this);

    QUrl url(act::mpei_url);
    QNetworkReply* reply = nam->get(QNetworkRequest(url));

    connect(nam, SIGNAL(finished(QNetworkReply *)), this, SLOT(onResult(QNetworkReply *)));

    timer->setInterval(config->GetInterval());
}

void MainWindow::notifyWithOutTray()
{
    QNetworkAccessManager* nam = new QNetworkAccessManager(this);

    QUrl url(act::mpei_url);
    QNetworkReply* reply = nam->get(QNetworkRequest(url));

    connect(nam, SIGNAL(finished(QNetworkReply *)), this, SLOT(onResultWithOutTray(QNetworkReply *)));
}

inline void MainWindow::SetUpTimer()
{
    timer = new QTimer(this);

    timer->setInterval(1);
    timer->start();
    connect(timer, &QTimer::timeout, this, &MainWindow::notify);
}

inline void MainWindow::SetUpSystemTrayIcon()
{
    tIcon = new QSystemTrayIcon();
    tIcon->setIcon(QIcon(":/icon/favicon.ico"));
}

void MainWindow::SetUpConfig()
{
    config = new SConfig();
    configJson = config->OpenConfigJson();
    config->HandleConfigJson(configJson);

    connect(tIcon, &QSystemTrayIcon::messageClicked, this, &MainWindow::MessageClicked);
    connect(tIcon, &QSystemTrayIcon::activated, this, &MainWindow::onActivated);
    config->WriteJson(config->GetJson());
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (arg1 == Qt::CheckState::Checked)
    {
        config->SetAutoRun(true);
        config->WriteJson(config->GetJson());
#ifdef Q_OS_WIN32
        QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        settings.setValue(act::AppName, QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
        settings.sync();
#endif
    }
    if (arg1 == Qt::CheckState::Unchecked)
    {
        config->SetAutoRun(false);
        config->WriteJson(config->GetJson());
#ifdef Q_OS_WIN32
        QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        settings.remove(act::AppName);
#endif
    }
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    uint64_t interval = arg1 * 60 * 60 * 1000;

    config->SetInterval(interval);
    config->WriteJson(config->GetJson());

    timer->stop();
    timer->setInterval(interval);
    timer->start();
}

void MainWindow::on_pushButton_clicked()
{
    config->WriteJson(config->GetJson());
}

