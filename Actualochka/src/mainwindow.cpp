#include "../include/Mainwindow/mainwindow.hpp"
#include "../include/General/confighandler.hpp"
#include "ui_mainwindow.h"

#include <QThread>
#include <QCheckBox>
#include <QSettings>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SetUpSystemTrayIcon();
    SetUpConfig();
    SetUpTimer();

    connect(ui->UpdateButton, &QPushButton::clicked, this, [&]()
    {
        auto nam = NetworReplyer::AccessUrl(act::MpeiActuallity);
        connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResultWithOutTray(QNetworkReply*)));
    });
}

MainWindow::~MainWindow()
{
    config->WriteJson(config->GetJson());

    for (auto& x : this->actions)
    {
        delete x;
    }
    delete context;
    delete tIcon;
    delete timer;
    delete config;
    delete ui;
}

void MainWindow::InitParams()
{
    ui->versionLabel->setText("v1.0.1");

    setWindowTitle("Актуалочка");
    setFixedSize(QSize(640, 480));

    ui->tabWidget->setTabText(0, tr("Информация"));
    ui->tabWidget->setTabText(1, tr("Настройки"));
    ui->tabWidget->setTabText(2, tr("Календарь"));
    ui->tabWidget->setCurrentIndex(0);
    ui->textEditShedule->setReadOnly(true);

    auto time = ((config->GetInterval() / 1000)/ 60) / 60;
    if (ui->spinBox)
        ui->spinBox->setValue(time);

    bool isChecked = config->isAutoRunEnable();
    if (ui->checkBox)
        ui->checkBox->setChecked(isChecked);
}

void MainWindow::onActivatedSetContent(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Unknown:
        tIcon->showMessage(QString("Актуалочка"), actuallyContent, QSystemTrayIcon::MessageIcon(QSystemTrayIcon::NoIcon));
        ui->textEdit->setText(actuallyContent);
        break;
    case QSystemTrayIcon::Context:
        tIcon->setContextMenu(context);
        break;
    case QSystemTrayIcon::Trigger:
        this->show();
        InitParams();
        break;
    case QSystemTrayIcon::MiddleClick:
    case QSystemTrayIcon::DoubleClick:
        break;
    }
}

void MainWindow::onActivatedSetSchedule()
{
    for (auto&x : scheduleContent)
    {
        QString ExistingText = ui->textEditShedule->toPlainText();
        if (!ExistingText.isEmpty())
        {
            ui->textEditShedule->setText(ExistingText + "\n\n" + x);
        }
        else
        {
            ui->textEditShedule->setText(x);
        }
    }
}

void MainWindow::onActivatedSetCalendar()
{
    auto calendar = ui->calendarWidget;
    calendar->setStyleSheet("QTableView{selection-background-color: #222;}");
    calendar->setMinimumDate(QDate().currentDate().addDays(-1));
    calendar->setMaximumDate(QDate().currentDate().addMonths(3));

    QTextCharFormat form = QTextCharFormat();;
    for (auto &x : scheduleCalendar)
    {
        if (x.lessionType == tr("Лекция"))
        {
            form.setBackground(QBrush(QColor("#444C55")));
        }
        else if (x.lessionType == tr("Практическое занятие"))
        {
            form.setBackground(QBrush(QColor("#2D333B")));
        }
        else
        {
            form.setBackground(QBrush(QColor("#22272E")));
        }

        form.setToolTip(x.lession + " - " + x.lessionType);
        form.setForeground(QBrush(QColor(255,255,255)));
        calendar->setDateTextFormat(x.date.date(), form);
    }
    ui->color1->setText(tr("Лекция"));
    ui->color2->setText(tr("Практическое занятие"));
    ui->color3->setText(tr("Лабораторное занятие"));

    ui->color1->setStyleSheet("QLabel { background-color : #444C55; color : white }");
    ui->color2->setStyleSheet("QLabel { background-color : #2D333B; color : white }");
    ui->color3->setStyleSheet("QLabel { background-color : #22272E; color : white }");
}

void MainWindow::MessageClicked()
{
    this->show();
    InitParams();
}

void MainWindow::SetToolTipTime()
{
    uint64_t remaingTime = timer->remainingTime() / 60000;
    QString suffix = "минут";

    if (remaingTime > 60)
    {
        remaingTime /= 60;
        suffix = "часов";
    }

    if (tIcon)
    {

        tIcon->setToolTip(QString::number(
            remaingTime) == QString::number(0) ?
            "Осталось " + QString::number(config->GetInterval() / (60 * 1000 * 60)) + " " + "часов" :
            "Осталось " + QString::number(remaingTime) + " " + suffix
            );
    }
}

void MainWindow::onResultActually(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        actuallyContent = ServerJsonParser::ParseJsonFromServer(reply, IEType::Actualochka).at(0);
    }
    else
    {
        actuallyContent = reply->errorString();
    }

    tIcon->setVisible(true);
    onActivatedSetContent(QSystemTrayIcon::Unknown);
}

void MainWindow::onResultSchedule(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        scheduleContent = ServerJsonParser::ParseJsonFromServer(reply, IEType::Schedule);
    }
    else
    {
        scheduleContent[0] = reply->errorString();
    }
    onActivatedSetSchedule();
}

void MainWindow::onResultScheduleMonth(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        scheduleCalendar = ServerJsonParser::ParseJsonMonth(reply);
        onActivatedSetCalendar();
    }
    else
    {
        qDebug() << "Can't get schedule at month";
    }
}

void MainWindow::onResultWithOutTray(QNetworkReply *reply)
{
    actuallyContent = ServerJsonParser::ParseJsonFromServer(reply, IEType::Actualochka).at(0);
    ui->textEdit->setText(actuallyContent);
}


inline void MainWindow::SetUpTimer()
{
    timer = new QTimer(this);

    timer->setInterval(1);
    timer->start();

    toolTipPpdater = new QTimer(this);
    toolTipPpdater->setInterval(60 * 1000);

    toolTipPpdater->start();

    connect(toolTipPpdater, &QTimer::timeout, this, &MainWindow::SetToolTipTime);
    connect(timer, &QTimer::timeout, this, [=]()
    {
        QString ScheduleMonthUrl = act::MpeiSchedule + "?start=" + QDate().currentDate().toString("yyyy.MM.dd") + "&finish=" + QDate().currentDate().addMonths(3).toString("yyyy.MM.dd");
        auto namA = NetworReplyer::AccessUrl(act::MpeiActuallity);
        auto namS = NetworReplyer::AccessUrl(act::MpeiSchedule);
        auto namM = NetworReplyer::AccessUrl(ScheduleMonthUrl);

        connect(namA, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResultActually(QNetworkReply*)));
        connect(namS, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResultSchedule(QNetworkReply*)));
        connect(namM, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResultScheduleMonth(QNetworkReply*)));
        timer->setInterval(config->GetInterval());
    });

    SetToolTipTime();
}

inline void MainWindow::SetUpSystemTrayIcon()
{
    tIcon = new QSystemTrayIcon();
    tIcon->setIcon(QIcon(":/icon/favicon.ico"));

    context = new QMenu();
    QAction *exit = new QAction(context);
    QAction *settingTab = new QAction(context);
    QAction *calendarTab = new QAction(context);

    exit->setText(tr("Выход"));
    settingTab->setText(tr("Настройки"));
    calendarTab->setText(tr("Календарь"));

    context->addAction(calendarTab);
    context->addAction(settingTab);
    context->addSeparator();
    context->addAction(exit);

    connect(exit, &QAction::triggered, this, [&](){
        emit ForceClose();
    });

    connect(settingTab, &QAction::triggered, this, [&](){
        show();
        ui->tabWidget->setCurrentIndex(1);
    });

    connect(calendarTab, &QAction::triggered, this, [&](){
        show();
        ui->tabWidget->setCurrentIndex(2);
    });

    actions.append(exit);
    actions.append(settingTab);
    actions.append(calendarTab);
}

void MainWindow::SetUpConfig()
{
    config = new SConfig();
    configJson = config->OpenConfigJson();
    config->HandleConfigJson(configJson);

    connect(tIcon, &QSystemTrayIcon::messageClicked, this, &MainWindow::MessageClicked);
    connect(tIcon, &QSystemTrayIcon::activated, this, &MainWindow::onActivatedSetContent);
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
    if (arg1 == 0)
    {
        timer->stop();
        config->SetInterval(Interval);
        config->WriteJson(config->GetJson());

        return;
    }

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
