#include "../include/System/calendardatehandler.hpp"

#include <QTextCharFormat>

CalendarDateHandler::CalendarDateHandler(QObject *parent) :
                                QObject(parent)
{
}

CalendarDateHandler::CalendarDateHandler(QCalendarWidget *tcalendar, QLabel *label1, QLabel *label2, QLabel *label3) :
                                calendar(tcalendar), lection(label1), practice(label2), labwork(label3)
{
    isDarkTheme = false;
    lection->setText(tr("Лекция"));
    practice->setText(tr("Практическое занятие"));
    labwork->setText(tr("Лабораторное занятие"));

    lection->setStyleSheet("QLabel { background-color : #bbbcbf; color : #26262d }");
    practice->setStyleSheet("QLabel { background-color : #a9e7e8; color : #26262d }");
    labwork->setStyleSheet("QLabel { background-color : #d6eee1; color : #26262d }");
}

void CalendarDateHandler::SetCalendarStyleByLessions()
{
    /* ------------------------------------- *
     *          Light theme
     *
     *  lection         #444C55
     *  practice        #2D333B
     *  labwork(other)  #22272E
     *  tableView #     222
     * -------------------------------------*/

    calendar->setStyleSheet("QTableView { selection-background-color: #26262d; } ");
    calendar->setMinimumDate(QDate().currentDate().addDays(-1));
    calendar->setMaximumDate(scheduleMonth.last().date.date());

    QTextCharFormat form = QTextCharFormat();
    for (QDate date = calendar->minimumDate(); date != calendar->maximumDate(); date = date.addDays(1))
    {
        form.setBackground(QBrush(QColor(255, 255, 255)));
        form.setToolTip("");
        calendar->setDateTextFormat(date, form);
    }

    for (auto &x : scheduleMonth)
    {
        if (x.lessionType == tr("Лекция"))
        {
            form.setBackground(QBrush(QColor("#bbbcbf")));
        }
        else if (x.lessionType == tr("Практическое занятие"))
        {
            form.setBackground(QBrush(QColor("#a9e7e8")));
        }
        else
        {
            form.setBackground(QBrush(QColor("#d6eee1")));
        }
        form.setToolTip(x.lession + " - " + x.lessionType);
        form.setForeground(QBrush(QColor(255, 255, 255)));
        calendar->setDateTextFormat(x.date.date(), form);
    }
}

void CalendarDateHandler::SetScheduleMonth(QVector<CellData> &scheduleMonth)
{
    this->scheduleMonth = scheduleMonth;
}

void CalendarDateHandler::SetDarkTheme(bool isDarkTheme)
{
    this->isDarkTheme = isDarkTheme;
}
