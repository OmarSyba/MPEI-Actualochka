#include "../include/Mainwindow/mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Актуалочка");

    SetUpTimer();
    SetUpSystemTrayIcon();
    SetUpConfig();
}

MainWindow::~MainWindow()
{
    delete tIcon;
    delete timer;
    delete config;
    delete ui;
}

void MainWindow::onActivated(QSystemTrayIcon::ActivationReason reason)
{
    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
    tIcon->showMessage(QString("Актуалочка"), content, icon, 1000000);
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

void MainWindow::notify()
{
    QNetworkAccessManager* nam = new QNetworkAccessManager(this);

    QUrl url(act::mpei_url);
    QNetworkReply* reply = nam->get(QNetworkRequest(url));

    connect(nam, SIGNAL(finished(QNetworkReply *)), this, SLOT(onResult(QNetworkReply *)));

    timer->setInterval(act::interval);
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

    config->HandleConfigJson(config->GetJson());
    config->SetAutoRun(false);
    config->WriteJson(config->GetJson());
}
