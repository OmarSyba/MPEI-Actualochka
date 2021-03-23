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
#include "../General/confighandler.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void InitParams();

public slots:
    void onActivated(QSystemTrayIcon::ActivationReason reason);
    void MessageClicked();

private slots:
    void onResult(QNetworkReply *reply);
    void onResultWithOutTray(QNetworkReply *reply);

    void notify();
    void notifyWithOutTray();

    void on_checkBox_stateChanged(int arg1);
    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_clicked();

private:
    inline void SetUpTimer();
    inline void SetUpSystemTrayIcon();
    inline void SetUpConfig();

private:
    QString content;
    Ui::MainWindow *ui;

    SConfig *config = nullptr;
    QSystemTrayIcon *tIcon = nullptr;
    QTimer *timer = nullptr;

    QJsonObject *configJson = nullptr;
};
#endif // MAINWINDOW_HPP
