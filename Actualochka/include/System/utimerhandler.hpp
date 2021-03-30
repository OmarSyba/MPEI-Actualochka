#ifndef UTIMERHANDLER_HPP
#define UTIMERHANDLER_HPP

#include <QObject>
#include <QTimer>

class UTimerHandler
{
    Q_OBJECT
public:
    UTimerHandler();
    UTimerHandler(quint64 ms);

private:
    QTimer *timer = nullptr;
};

#endif // UTIMERHANDLER_HPP
