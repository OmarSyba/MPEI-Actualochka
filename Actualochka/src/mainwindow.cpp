#include "../include/Mainwindow/mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <QKeyEvent>
#include <QCheckBox>
#include <QTimer>
#include <QSettings>

//#define NORECIEVE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Start Maimwindow construct";
    ui->setupUi(this);
    InitWindowParameters();
    InitPrivateParameters();
#ifndef NORECIEVE
    MakeReceive();
#endif
}

MainWindow::~MainWindow()
{
    delete calendar;
    delete web;
    delete timer;
    delete sysTray;
    delete config;
    delete ui;
}

void MainWindow::InitWindowParameters()
{
    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Set up window parameters";
    setWindowTitle(tr("Актуалочка"));
    resize(QSize(640, 480));
    setMinimumSize(QSize(640, 480));

    ui->tabWidget->setTabText(0, tr("Информация"));
    ui->tabWidget->setTabText(1, tr("Настройки"));
    ui->tabWidget->setTabText(2, tr("Календарь"));
    ui->tabWidget->setTabText(3, tr("Конспекты"));
    ui->tabWidget->setCurrentIndex(0);
    ui->textEditShedule->setReadOnly(true);
    ui->labelVersion->setText(act::CurrnetVersion);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qWarning(logWarning()) << " [" << __FUNCTION__ << "] --- " << "Esc was pressed";
    if (event->key() == Qt::Key_Escape)
    {
        close();
    }
}

void MainWindow::onResultActually(QNetworkReply *reply)
{
    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Get result actuallity";
    content.Actuallity = reply->error() == QNetworkReply::NoError ?
                ServerJsonParser::ParseJsonFromServer(reply, EReply_Type::Actualochka).at(0) :
                reply->errorString();

    if (config->isNotifyEnabled())
    {
        sysTray->showMessage(tr("Актуалочка"), content.Actuallity, QSystemTrayIcon::MessageIcon(QSystemTrayIcon::NoIcon));
    }
    ui->textEditActuallity->setText(content.Actuallity);
    reply->deleteLater();

    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Actualochka reply finished";
}

void MainWindow::onResultSchedule(QNetworkReply *reply)
{
    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Get result schedule";
    content.ScheduleWeek = reply->error() == QNetworkReply::NoError ?
                ServerJsonParser::ParseJsonFromServer(reply, EReply_Type::ScheduleWeek):
                QVector<QString>(reply->errorString());

    ui->textEditShedule->clear();
    for (auto&x : content.ScheduleWeek)
    {
        QString ExistingText = ui->textEditShedule->toPlainText();
        ui->textEditShedule->setText(!ExistingText.isEmpty() ? ExistingText + "\n\n" + x : x);
    }
    reply->deleteLater();

    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Schedule reply finished";
}

void MainWindow::onResultScheduleMonth(QNetworkReply *reply)
{
    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Get result schedule month";
    if (reply->error() == QNetworkReply::NoError)
    {
        content.ScheduleMonth = ServerJsonParser::ParseJsonMonth(reply);
        calendar->SetScheduleMonth(content.ScheduleMonth);
        calendar->SetCalendarStyleByLessions();
    }
    reply->deleteLater();

    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Schedule month reply finished";
}

void MainWindow::onAutoRunChanged(int state)
{
    if (state == Qt::Checked)
    {
        qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Auto Run checked";
        config->SetAutoRunEnabled(true);
        config->SaveConfigIntoFile();
#ifdef Q_OS_WIN32
        QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        settings.setValue(act::AppName, QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
        settings.sync();
#endif
    }
    else
    {
        qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Auto Run unchecked";
        config->SetAutoRunEnabled(false);
        config->SaveConfigIntoFile();
#ifdef Q_OS_WIN32
        QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        settings.remove(act::AppName);
#endif
    }
}

void MainWindow::onNotifyChanged(int tstate)
{
    bool state = Qt::Checked == tstate;
    config->SetNotifyEnabled(state);
    ui->spinBoxInterval->setReadOnly(!state);
    !state ? timer->StopTimer() : timer->StartTimer();
    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Notify enabled changed";
}

void MainWindow::onDarkThemeChanged(int tstate)
{
    bool state = Qt::Checked == tstate;
    config->SetDarkTheme(state);
    setUpStyleApp(*static_cast<QApplication *>(QApplication::instance()), state);

    manager.notify(state);
}

void MainWindow::onComboBoxActivated(int index)
{
    QString title = ui->comboBoxGroup->itemText(index);
    quint32 id = content.Groups[title];

    config->SetGroupName(title);
    config->SetGroupId(id);

    id != act::Group40a20 ?
                ui->textEditActuallity->setText("Для вашей группы актуалочка недоступна") :
                ui->textEditActuallity->setText(content.Actuallity);

#ifndef NORECIEVE
    QString ScheduleShort = act::MpeiSchedule + "?group=" + QString::number(id);
    QString ScheduleMonthUrl = act::MpeiSchedule + "?group=" + QString::number(id) + "&start=" +
       QDate().currentDate().toString("yyyy.MM.dd") +
       "&finish=" + QDate().currentDate().addMonths(3).toString("yyyy.MM.dd");

    auto namA = web->AccsessUrl(ScheduleShort);
    auto namS = web->AccsessUrl(ScheduleMonthUrl);

    connect(namA, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResultSchedule(QNetworkReply*)));
    connect(namS, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResultScheduleMonth(QNetworkReply*)));
#endif
    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Combo box activated";
}

void MainWindow::onSpinBoxValueChanged(int value)
{
    config->SetInterval(value * act::oneHour);
    timer->StopTimer();
    timer->SetTimer(value * act::oneHour);
    timer->StartTimer();
    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Spin Box changed";
}

void MainWindow::onSysTrayActivated(QSystemTrayIcon::ActivationReason reason)
{
    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Sys tray activated. ReasonID = " << reason;
    switch (reason)
    {
        break;
    case QSystemTrayIcon::Trigger:
        show();
        break;
    case QSystemTrayIcon::Context:
    case QSystemTrayIcon::MiddleClick:
    case QSystemTrayIcon::DoubleClick:
    case QSystemTrayIcon::Unknown:
        break;
    }
}

void MainWindow::InitPrivateParameters()
{
    config = new ConfigerExplorer(this);
    config->OpenJsonConfig();

    sysTray = new USystemTray(this);
    timer = new UTimerHandler(config->GetInterval());
    web = new UWebHandler(this);

    calendar = new CalendarDateHandler(ui->calendarWidget, ui->color1, ui->color2, ui->color3, config->isDarkTheme());
    calendar->SetDarkTheme(config->isDarkTheme());
    manager.subscribe(calendar);

    SetUpSettingsTab();
    setUpStyleApp(*static_cast<QApplication *>(QApplication::instance()), config->isDarkTheme());
    SetUpConnects();
    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Initial basic ptrs";
}

void MainWindow::SetUpSettingsTab()
{
    ui->checkBoxAutoRun->setChecked(config->isAutoRunEnabled());
    ui->checkBoxNotify->setChecked(config->isNotifyEnabled());
    ui->spinBoxInterval->setValue(config->GetInterval() / act::oneHour);
    ui->spinBoxInterval->setReadOnly(!config->isNotifyEnabled());
    ui->checkBoxDarkTheme->setChecked(config->isDarkTheme());

    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Set up settings tab";
}

void MainWindow::GetListOfGroups(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        content.Groups = ServerJsonParser::ParseGroups(reply);
        ui->comboBoxGroup->addItems(content.Groups.keys());
        auto containerKeys = content.Groups.keys();
        auto containerValues = content.Groups.values();

        for (quint32 idx = 0; idx < containerKeys.length(); ++idx)
        {
            if (config->GetGroupId() == containerValues.at(idx))
            {
                ui->comboBoxGroup->setCurrentIndex(idx);
                break;
            }
        }
    }
    reply->deleteLater();
    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Group list reply finished";
}

void MainWindow::onResultCheckForUpdate(QNetworkReply *reply)
{
     QString version = "v" + ServerJsonParser::ParseVersion(reply);
     qWarning(logWarning()) << " [" << __FUNCTION__ << "] --- " << "Version on pc : " << act::CurrnetVersion << " -- Version on server : " << version;
     if (version != act::CurrnetVersion)
     {
         emit newversion();
     }
     reply->deleteLater();
     qWarning(logWarning()) << " [" << __FUNCTION__ << "] --- " << "Version get pressed";
}

void MainWindow::SetUpConnects()
{
    connect(sysTray->GetSettingsAction(), &QAction::triggered, this, [&]()
    {
        ui->tabWidget->setCurrentIndex(1);
        show();
    });
    qWarning(logWarning()) << " [" << __FUNCTION__ << "] --- " << "Sys tray connect settings";

    connect(sysTray->GetDevConnectAction(), &QAction::triggered, this, [&]()
    {
        QDesktopServices::openUrl(tr("https://vk.com/koalian"));
        QDesktopServices::openUrl(tr("https://vk.com/id45052566"));
    });

    connect(sysTray->GetCalendarAction(), &QAction::triggered, this, [&]()
    {
        ui->tabWidget->setCurrentIndex(2);
        show();
    });

    qWarning(logWarning()) << " [" << __FUNCTION__ << "] --- " << "Sys tray calendar";

    connect(sysTray->GetExitAction(), &QAction::triggered, this, [&]()
    {
        contentManager.saveContent(ContentFile { ui->textEditActuallity->toPlainText(), ui->textEditShedule->toPlainText() });
        emit quitapp();
    });
    qWarning(logWarning()) << " [" << __FUNCTION__ << "] --- " << "Close connect";

    connect(sysTray, &USystemTray::messageClicked, this, [&]()
    {
        ui->tabWidget->setCurrentIndex(0);
        show();
    });

    qWarning(logWarning()) << " [" << __FUNCTION__ << "] --- " << "Message clicked connect";

    connect(ui->checkupdateButton, &QPushButton::clicked, this, [&]()
    {
        auto namVersion = web->AccsessUrl(act::MpeiVersion);
        connect(namVersion, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResultCheckForUpdate(QNetworkReply*)));
    });

    qWarning(logWarning()) << " [" << __FUNCTION__ << "] --- " << "Version update connect";

    connect(sysTray, &QSystemTrayIcon::activated, this, &MainWindow::onSysTrayActivated);
    connect(ui->checkBoxAutoRun, SIGNAL(stateChanged(int)), this, SLOT(onAutoRunChanged(int)));
    connect(ui->checkBoxNotify, SIGNAL(stateChanged(int)), this, SLOT(onNotifyChanged(int)));
    connect(ui->pushButtonSave, &QPushButton::clicked, this, [&]() { config->SaveConfigIntoFile(); });
    connect(ui->comboBoxGroup, SIGNAL(activated(int)), this, SLOT(onComboBoxActivated(int)));
    connect(ui->spinBoxInterval, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxValueChanged(int)));
    connect(ui->checkBoxDarkTheme, SIGNAL(stateChanged(int)), this, SLOT(onDarkThemeChanged(int)));

//    if (ServerJsonParser::isOnline())
//    {
//        ConnectOnlineSlots();
//    }
//    else
//    {
//        qCritical(logCritical()) << " [" << __FUNCTION__ << "] --- " << "Device offline";
//    }
    ConnectOnlineSlots();
    qCritical(logCritical()) << " [" << __FUNCTION__ << "] --- " << "Set up connects";
}

void MainWindow::MakeReceive()
{
    qCritical(logCritical()) << " [" << __FUNCTION__ << "] --- " << "Make request";

    content.Groups.clear();
    ui->comboBoxGroup->clear();

    QString groupUrl = act::MpeiSchedule + "?group=" + QString::number(config->GetGroupId());

    QString ScheduleMonthUrl = act::MpeiSchedule + "?group=" + QString::number(config->GetGroupId()) + "&start=" +
                    QDate().currentDate().toString("yyyy.MM.dd") +
                    "&finish=" + QDate().currentDate().addMonths(3).toString("yyyy.MM.dd");

    auto namActuallity = web->AccsessUrl(act::MpeiActuallity);
    auto namScheduleWeek = web->AccsessUrl(groupUrl);
    auto namMonth = web->AccsessUrl(ScheduleMonthUrl);
    auto namGroups = web->AccsessUrl(act::MpeiGroupList);

    connect(namActuallity, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResultActually(QNetworkReply*)));
    connect(namScheduleWeek, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResultSchedule(QNetworkReply*)));
    connect(namMonth, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResultScheduleMonth(QNetworkReply*)));
    connect(namGroups, SIGNAL(finished(QNetworkReply*)), this, SLOT(GetListOfGroups(QNetworkReply*)));
}

void MainWindow::ConnectOnlineSlots()
{
    connect(timer->GetCurrentTimer(), &QTimer::timeout, this, &MainWindow::MakeReceive);
    connect(ui->UpdateButton, &QPushButton::clicked, this, &MainWindow::MakeReceive);
}
