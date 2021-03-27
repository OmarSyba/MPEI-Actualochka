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
    case IEType::Schedule:
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

QVector<CellData> ServerJsonParser::ParseJsonMonth(QNetworkReply *reply)
{
    QVector<CellData> result;

    auto jsonArray = QJsonDocument::fromJson(
                QString(reply->readAll()).toUtf8())
                .object()["schedule"].toArray();

    for (auto&& x : jsonArray)
    {
        QJsonObject obj = x.toObject();
        CellData data;

        data.date = QDateTime::fromString(obj["date"].toString(), "yyyy.MM.dd");
        data.lession = obj["discipline"].toString();
        data.lessionType = obj["kindOfWork"].toString();

        result.append(data);
    }

    return result;
}

QString ServerJsonParser::ParseVersion(QNetworkReply *reply)
{
    return QJsonDocument::fromJson(QString(reply->readAll()).toUtf8()).object()["version"].toString();
}
