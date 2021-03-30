#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "include/General/general.hpp"
#include "include/General/configerexplorer.hpp"
#include "include/System/usystemtray.hpp"
#include "include/System/utimerhandler.hpp"
#include "include/System/uwebhandler.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    virtual void keyPressEvent(QKeyEvent *event) final;
    void InitWindowParameters();

public slots:
    void onResultSchedule(QNetworkReply *reply);

private:
    void InitPrivateParameters();
    void SetUpSettingsTab();
    void SetUpConnects();

signals:
    void quitapp();

private:
    ConfigerExplorer  *config  = nullptr;
    USystemTray       *sysTray = nullptr;
    UTimerHandler     *timer   = nullptr;
    UWebHandler       *web     = nullptr;
    Ui::MainWindow    *ui      = nullptr;

};
#endif // MAINWINDOW_HPP
