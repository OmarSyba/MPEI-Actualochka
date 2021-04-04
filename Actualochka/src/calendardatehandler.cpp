#include "../include/System/calendardatehandler.hpp"

#include <QTextCharFormat>

CalendarDateHandler::CalendarDateHandler(QObject *parent) :
                                QObject(parent)
{
}

CalendarDateHandler::CalendarDateHandler(QCalendarWidget *tcalendar, QLabel *label1, QLabel *label2, QLabel *label3) :
                                calendar(tcalendar), lection(label1), practice(label2), labwork(label3)
{
    lection->setText(tr("Лекция"));
    practice->setText(tr("Практическое занятие"));
    labwork->setText(tr("Лабораторное занятие"));

    lection->setStyleSheet("QLabel { background-color : #444C55; color : white }");
    practice->setStyleSheet("QLabel { background-color : #2D333B; color : white }");
    labwork->setStyleSheet("QLabel { background-color : #22272E; color : white }");
}

void CalendarDateHandler::SetCalendarStyleByLessions()
{
    calendar->setStyleSheet("QTableView{selection-background-color: #222;}");
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
            form.setBackground(QBrush(QColor("#444C55")));
        }
        else if (x.lessionType == tr("Практическое занятие"))
        {
            form.setBackground(QBrush(QColor("#2D333B")));
        }
        else
        {
            form.setBackground(QBrush(QColor("#22272E")));
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
