#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <QString>
#include <QDir>
#include <QLoggingCategory>
#include <QApplication>

#include "include/General/themechanger.hpp"

Q_DECLARE_LOGGING_CATEGORY(logDebug)
Q_DECLARE_LOGGING_CATEGORY(logInfo)
Q_DECLARE_LOGGING_CATEGORY(logWarning)
Q_DECLARE_LOGGING_CATEGORY(logCritical)
Q_DECLARE_LOGGING_CATEGORY(logFatal)

struct CellData
{
    QDateTime date;
    QString lessionType;
    QString lession;
};

struct Content
{
    QString Actuallity;
    QVector<QString> ScheduleWeek;
    QVector<CellData> ScheduleMonth;
    QMap<QString, quint32> Groups;
};

static QScopedPointer<QFile> gFile;
void setUpStyleApp(QApplication& app, bool isDark);

namespace act
{
    [[maybe_unused]] static constexpr quint64 oneHour = 1000 * 60 * 60;
    [[maybe_unused]] static quint64 Interval = 2880000;
    [[maybe_unused]] static quint16 Group40a20 = 12861;

    static QString CurrnetVersion = "v1.3.5";
    static QString MpeiActuallity = "https://mpei-server.herokuapp.com/getActuality";
    static QString MpeiSchedule = "https://mpei-server.herokuapp.com/getSchedule";
    static QString MpeiVersion = "https://mpei-server.herokuapp.com/version";
    static QString ConfigPath = QString("C:/ProgramData/Actualochka") + QString("/config.json");
    static QString AppName = "Actualochka";
    static QString MpeiGroupList = "https://mpei-server.herokuapp.com/getStudentsGroups";
};

#endif // GENERAL_HPP
