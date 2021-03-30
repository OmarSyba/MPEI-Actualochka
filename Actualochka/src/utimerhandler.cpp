#include "include/System/utimerhandler.hpp"

UTimerHandler::UTimerHandler() : timer(new QTimer(this))
{

}

UTimerHandler::UTimerHandler(quint64 ms)
{
    UTimerHandler();
    timer->setInterval(ms);
}

void UTimerHandler::SetTimer(quint64 ms)
{
    timer->setInterval(ms);
}

void UTimerHandler::StartTimer() const
{
    timer->start();
}

quint64 UTimerHandler::GetRemainingTimeTimer() const
{
    return timer->remainingTime() / act::oneHour;
}

UTimerHandler::~UTimerHandler()
{
    delete timer;
}
