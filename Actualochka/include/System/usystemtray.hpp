#ifndef USYSTEMTRAY_HPP
#define USYSTEMTRAY_HPP

#include <QSystemTrayIcon>
#include <QObject>

class USystemTray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    USystemTray();
};

#endif // USYSTEMTRAY_HPP
