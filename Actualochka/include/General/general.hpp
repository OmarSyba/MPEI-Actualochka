#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <QString>
#include <QDir>

//Template url
//https://mpei-server.herokuapp.com/api/getSchedule?start=2021.03.22&finish=2021.04.22
//https://mpei-server.herokuapp.com/api/getStudentsGroups

static QString logdir = QString("C:/ProgramData/Actualochka");
static QFile logfile(logdir + "/Act.log");

namespace act
{
    [[maybe_unused]] static constexpr quint64 oneHour = 1000 * 60 * 60;
    [[maybe_unused]]static quint64 Interval = 2880000;

    static QString CurrnetVersion = "v1.1.1b";
    static QString MpeiActuallity = "https://mpei-server.herokuapp.com/api/getActuality";
    static QString MpeiSchedule = "https://mpei-server.herokuapp.com/api/getSchedule";
    static QString MpeiVersion = "https://mpei-win.herokuapp.com/version";
    static QString ConfigPath = logdir + "/config.json";
    static QString AppName = "Actualochka";
    static QString MpeiGroupList = "https://mpei-server.herokuapp.com/api/getStudentsGroups";
}

#endif // GENERAL_HPP
