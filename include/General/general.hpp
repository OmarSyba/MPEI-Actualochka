#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <QString>
#include <QDir>

namespace act
{
    static QString MpeiActuallity = "https://mpei-server.herokuapp.com/api/getActuality";
    static QString MpeiSchedule = "https://mpei-server.herokuapp.com/api/getSchedule";
    static uint32_t Interval = 28800000;
    static QString ConfigPath = QDir::currentPath() + "/config.json";
    static QString AppName = "Actualochka";
}

#endif // GENERAL_HPP
