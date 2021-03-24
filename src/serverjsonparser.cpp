#include "../include/Receiver/serverjsonparser.hpp"

#include <QVector>

QVector<QString> ServerJsonParser::ParseJsonFromServer(QNetworkReply *reply, IEType type)
{
    QVector<QString> result;
    switch (type)
    {
    case IEType::Actualochka:
        result.append(QJsonDocument::fromJson(
                    QString(reply->readAll()).toUtf8())
                    .object()["actuality"].toObject()["content"].toString());
        break;
    case IEType::Shedule:
        auto jsonArray = QJsonDocument::fromJson(
                    QString(reply->readAll()).toUtf8())
                    .object()["schedule"].toArray();
        result = ParseJson(jsonArray);
        break;
    }
    return result;
}

QVector<QString> ServerJsonParser::ParseJson(QJsonArray &tjsonArray)
{
    QVector<QString> schedule;

    for (auto&& x : tjsonArray)
    {
        QJsonObject obj = x.toObject();
        QString dayOfWeekString     = obj["dayOfWeekString"].toString();
        QString discipline          = obj["discipline"].toString();
        QString date                = obj["date"].toString();
        QString kindOfWork          = obj["kindOfWork"].toString();
        QString beginLesson         = obj["beginLesson"].toString();
        QString endLesson           = obj["endLesson"].toString();
        QString lecturer            = obj["lecturer"].toString();

        QString resultString = "[" + dayOfWeekString + "] "         +
                discipline + " - " + date + "\n"                    +
                " - " + kindOfWork + "\n"                          +
                " - " + beginLesson + " - " + endLesson + "\n"     +
                " - " + lecturer;
        schedule.append(resultString);
    }
    return schedule;
}
