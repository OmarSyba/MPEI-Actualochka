#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <QString>
#include <QDir>

//Template url
//https://mpei-server.herokuapp.com/api/getSchedule?start=2021.03.22&finish=2021.04.22

static QString logdir = QString("C:/ProgramData/Actualochka");
static QFile logfile(logdir + "/Act.log");

namespace act
{
    static QString CurrnetVersion = "1.0.4";
    static QString MpeiActuallity = "https://mpei-server.herokuapp.com/api/getActuality";
    static QString MpeiSchedule = "https://mpei-server.herokuapp.com/api/getSchedule";
    static QString MpeiVersion = "https://mpei-win.herokuapp.com/version";
    static QString ConfigPath = logdir + "/config.json";
    static QString AppName = "Actualochka";
}

#endif // GENERAL_HPP
