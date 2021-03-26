#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QTimer>

#include "../General/general.hpp"
#include "../General/confighandler.hpp"
#include "../Receiver/serverjsonparser.hpp"
#include "../Receiver/networreplyer.hpp"

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
    void SetToolTipTime();

private slots:
    void onResultActually(QNetworkReply *reply);
    void onResultSchedule(QNetworkReply *reply);
    void onResultScheduleMonth(QNetworkReply *reply);
    void onResultWithOutTray(QNetworkReply *reply);

    void onActivatedSetContent(QSystemTrayIcon::ActivationReason reason);
    void onActivatedSetSchedule();

    void onActivatedSetCalendar();
    void MessageClicked();

    void on_checkBox_stateChanged(int arg1);
    void on_spinBox_valueChanged(int arg1);
    void on_pushButton_clicked();

private:
    inline void SetUpTimer();
    inline void SetUpSystemTrayIcon();
    inline void SetUpConfig();

signals:
    void ForceClose();

private:
    QString actuallyContent;
    QVector<QString> scheduleContent;
    QVector<CellData> scheduleCalendar;
    QTime time;

    Ui::MainWindow *ui;
    QMenu *context = nullptr;
    QVector<QAction *> actions;

    SConfig *config = nullptr;
    QSystemTrayIcon *tIcon = nullptr;

    QTimer *timer = nullptr;
    QTimer *toolTipPpdater = nullptr;

    QJsonObject *configJson = nullptr;
};
#endif // MAINWINDOW_HPP
