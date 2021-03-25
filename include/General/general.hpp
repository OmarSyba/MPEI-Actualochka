#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <QString>
#include <QDir>

//Template url
//https://mpei-server.herokuapp.com/api/getSchedule?start=2021.03.22&finish=2021.04.22

namespace act
{
    static QString MpeiActuallity = "https://mpei-server.herokuapp.com/api/getActuality";
    static QString MpeiSchedule = "https://mpei-server.herokuapp.com/api/getSchedule";
    static QString ConfigPath = QDir::currentPath() + "/config.json";
    static QString AppName = "Actualochka";
}

#endif // GENERAL_HPP
