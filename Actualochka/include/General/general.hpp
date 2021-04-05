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

    static QString CurrnetVersion = "v1.2.0";
    static QString MpeiActuallity = "https://mpei-server.herokuapp.com/api/getActuality";
    static QString MpeiSchedule = "https://mpei-server.herokuapp.com/api/getSchedule";
    static QString MpeiVersion = "https://mpei-win.herokuapp.com/version";
    static QString ConfigPath = QString("C:/ProgramData/Actualochka") + QString("/config.json");
    static QString AppName = "Actualochka";
    static QString MpeiGroupList = "https://mpei-server.herokuapp.com/api/getStudentsGroups";
};

#endif // GENERAL_HPP
