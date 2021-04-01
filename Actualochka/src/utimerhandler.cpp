#include "include/System/utimerhandler.hpp"

UTimerHandler::UTimerHandler() : timer(new QTimer(this))
{

}

UTimerHandler::UTimerHandler(quint64 ms)
{
    timer = new QTimer(this);
    timer->setInterval(ms);
    interval = ms;
}

void UTimerHandler::SetTimer(quint64 ms)
{
    interval = ms;
    timer->setInterval(ms);
}

void UTimerHandler::StartTimer() const
{
    timer->stop();
    timer->setInterval(interval);
    timer->start();
}

void UTimerHandler::StopTimer() const
{
    timer->stop();
}

quint64 UTimerHandler::GetRemainingTimeTimer() const
{
    return timer->remainingTime();
}

QTimer *UTimerHandler::GetCurrentTimer() const
{
    return timer;
}

UTimerHandler::~UTimerHandler()
{
    delete timer;
}
