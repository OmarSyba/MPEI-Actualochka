#ifndef CALENDARDATEHANDLER_HPP
#define CALENDARDATEHANDLER_HPP

#include <QObject>
#include <QCalendarWidget>
#include <QLabel>

#include "include/General/general.hpp"
#include "include/System/serverjsonparser.hpp"

class CalendarDateHandler : public QObject
{
    Q_OBJECT
public:
    explicit CalendarDateHandler(QObject *parent = nullptr);
    explicit CalendarDateHandler(QCalendarWidget *calendar, QLabel *label1, QLabel *label2, QLabel *label3);

    void SetCalendarStyleByLessions();
    void SetScheduleMonth(QVector<CellData>& scheduleMonth);
    void SetDarkTheme(bool isDarkTheme);

private:

    bool isDarkTheme;
    QVector<CellData> scheduleMonth;
    QCalendarWidget *calendar;
    QLabel *lection;
    QLabel *practice;
    QLabel *labwork;
};

#endif // CALENDARDATEHANDLER_HPP
