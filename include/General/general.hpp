#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <QString>
#include <QDir>

namespace act
{
    static QString mpei_url = "https://mpei-server.herokuapp.com/api/getActuality";
    static uint32_t interval = 28800000;

    static QString configPath = QDir::currentPath() + "/config.json";
    static QString AppName = "Actualochka";
}

#endif // GENERAL_HPP
