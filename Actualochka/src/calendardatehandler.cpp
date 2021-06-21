#include "../include/System/calendardatehandler.hpp"

#include <QTextCharFormat>

CalendarDateHandler::CalendarDateHandler(QCalendarWidget *tcalendar, QLabel *label1, QLabel *label2, QLabel *label3) :
                                CalendarDateHandler(tcalendar, label1, label2, label3, false)
{
}

CalendarDateHandler::CalendarDateHandler(QCalendarWidget *tcalendar, QLabel *label1, QLabel *label2, QLabel *label3, bool isDark) :
                                isDarkTheme(isDark), calendar(tcalendar), lection(label1), practice(label2), labwork(label3)
{
    lection->setText(tr("Лекция"));
    practice->setText(tr("Практическое занятие"));
    labwork->setText(tr("Лабораторное занятие"));

    SetDarkTheme(isDarkTheme);
}

void CalendarDateHandler::SetDarkTheme(bool isDark)
{
    isDarkTheme = isDark;
    if (isDarkTheme)
    {
        lection->setStyleSheet("QLabel { background-color : #bbbcbf; color : #26262d }");
        practice->setStyleSheet("QLabel { background-color : #a9e7e8; color : #26262d }");
        labwork->setStyleSheet("QLabel { background-color : #d6eee1; color : #26262d }");
    }
    else
    {
        lection->setStyleSheet("QLabel { background-color : #444C55; color : white }");
        practice->setStyleSheet("QLabel { background-color : #2D333B; color : white }");
        labwork->setStyleSheet("QLabel { background-color : #22272E; color : white }");
    }

    QTextCharFormat form = QTextCharFormat();
    form.setBackground(QBrush(isDarkTheme ? QColor("#3e3e3e") : Qt::white));
    form.setForeground(QBrush(isDarkTheme ? Qt::white : QColor("#26262d")));

    for (auto &x : scheduleMonth)
    {
        if (x.lessionType == tr("Лекция"))
        {
            form.setBackground(QBrush(QColor(isDarkTheme ? "#bbbcbf" : "#444C55")));
        }
        else if (x.lessionType == tr("Практическое занятие"))
        {
            form.setBackground(QBrush(QColor(isDarkTheme ? "#a9e7e8" : "#2D333B")));
        }
        else
        {
            form.setBackground(QBrush(QColor(isDarkTheme ? "#d6eee1" : "#22272E")));
        }

        form.setToolTip(calendar->dateTextFormat(x.date.date()).toolTip());
        form.setForeground(QBrush(isDarkTheme ? QColor("#26262d") : Qt::white ));
        calendar->setDateTextFormat(x.date.date(), form);
    }
}

void CalendarDateHandler::update(bool isDark)
{
    SetDarkTheme(isDark);
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
    calendar->setMaximumDate(!scheduleMonth.empty() ? scheduleMonth.last().date.date() : QDate().currentDate().addDays(30));

    QTextCharFormat form = QTextCharFormat();
    for (QDate date = calendar->minimumDate(); date != calendar->maximumDate(); date = date.addDays(1))
    {
        form.setBackground(QBrush(isDarkTheme ? QColor("#3e3e3e") : Qt::white));
        form.setForeground(QBrush(isDarkTheme ? Qt::white : QColor("#26262d")));
        form.setToolTip("");
        calendar->setDateTextFormat(date, form);
    }

    for (auto &x : scheduleMonth)
    {
        if (x.lessionType == tr("Лекция"))
        {
            form.setBackground(QBrush(QColor(isDarkTheme ? "#bbbcbf" : "#444C55")));
        }
        else if (x.lessionType == tr("Практическое занятие"))
        {
            form.setBackground(QBrush(QColor(isDarkTheme ? "#a9e7e8" : "#2D333B")));
        }
        else
        {
            form.setBackground(QBrush(QColor(isDarkTheme ? "#d6eee1" : "#22272E")));
        }

        QString toolTip = calendar->dateTextFormat(x.date.date()).toolTip();
        QString newToolTip =    x.lession + " - " + x.lessionType + " " +
                                x.date.time().toString("hh:mm");

        form.setToolTip(toolTip.isEmpty() ?
                            newToolTip :
                            toolTip + "\n" + newToolTip);

        form.setForeground(QBrush(isDarkTheme ? QColor("#26262d") : Qt::white ));
        calendar->setDateTextFormat(x.date.date(), form);
    }
}

void CalendarDateHandler::SetScheduleMonth(QVector<CellData> &scheduleMonth)
{
    this->scheduleMonth = scheduleMonth;
}
