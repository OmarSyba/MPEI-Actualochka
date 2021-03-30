#ifndef UTIMERHANDLER_HPP
#define UTIMERHANDLER_HPP

#include <QObject>
#include <QTimer>

#include "include/General/general.hpp"

class UTimerHandler : public QObject
{
    Q_OBJECT
public:
    UTimerHandler();
    UTimerHandler(quint64 ms);

    void SetTimer(quint64 ms);
    void StartTimer() const;

    QTimer *GetTimer() const;
    QTimer *GetToolTipTimer() const;

    quint64 GetRemainingTimeTimer() const;

    virtual ~UTimerHandler();

private:
    QTimer *timer = nullptr;
};

#endif // UTIMERHANDLER_HPP
