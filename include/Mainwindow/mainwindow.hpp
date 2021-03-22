#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QSystemTrayIcon>

#include <QTimer>

#include "../General/general.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onActivated(QSystemTrayIcon::ActivationReason reason);

private slots:
    void onResult(QNetworkReply *reply);
    void Emmitier();

private:
    QString content;

    Ui::MainWindow *ui;

    QSystemTrayIcon *tIcon = nullptr;
    QTimer *timer = nullptr;
};
#endif // MAINWINDOW_HPP
