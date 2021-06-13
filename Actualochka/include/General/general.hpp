#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <QString>
#include <QDir>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(logDebug)
Q_DECLARE_LOGGING_CATEGORY(logInfo)
Q_DECLARE_LOGGING_CATEGORY(logWarning)
Q_DECLARE_LOGGING_CATEGORY(logCritical)
Q_DECLARE_LOGGING_CATEGORY(logFatal)

static QScopedPointer<QFile> gFile;

namespace act
{
    [[maybe_unused]] static constexpr quint64 oneHour = 1000 * 60 * 60;
    [[maybe_unused]] static quint64 Interval = 2880000;

    static QString CurrnetVersion = "v1.2.6";
    static QString MpeiActuallity = qgetenv("MPEI_ACT");
    static QString MpeiSchedule = qgetenv("MPEI_SCH");
    static QString MpeiVersion = qgetenv("MPEI_VER");
    static QString ConfigPath = QString("C:/ProgramData/Actualochka") + QString("/config.json");
    static QString AppName = "Actualochka";
    static QString MpeiGroupList = qgetenv("MPEI_GRP");
};

#endif // GENERAL_HPP
