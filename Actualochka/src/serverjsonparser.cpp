#include "../include/System/serverjsonparser.hpp"
#include <QEventLoop>

bool ServerJsonParser::isOnline()
{
    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl(QString("https://google.com")));
    QNetworkReply *reply = nam.get(req);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    return reply->bytesAvailable();
}

QMap<QString, quint32> ServerJsonParser::ParseGroups(QNetworkReply *reply)
{
    auto arrayJson = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8()).object()["studentsGroups"].toArray();
    return ParseJsonGroups(arrayJson);
}

QVector<QString> ServerJsonParser::ParseJsonFromServer(QNetworkReply *reply, EReply_Type type)
{
    QVector<QString> result;
    switch (type)
    {
    case EReply_Type::Actualochka:
        result.append(QJsonDocument::fromJson(
                    QString(reply->readAll()).toUtf8())
                    .object()["actuality"].toObject()["content"].toString());
        break;
    case EReply_Type::ScheduleWeek:
        auto jsonArray = QJsonDocument::fromJson(
                    QString(reply->readAll()).toUtf8())
                    .object()["schedule"].toArray();
        result = ParseJson(jsonArray);
        break;
    }
    return result;
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
        data.date.setTime(QTime::fromString(obj["beginLesson"].toString()));
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

QMap<QString, quint32> ServerJsonParser::ParseJsonGroups(QJsonArray &tjsonArray)
{
    QMap<QString, quint32> result;

    for(auto&& x : tjsonArray)
    {
        QJsonObject obj = x.toObject();
        quint32 groupId = obj["id"].toInt();
        QString groupName = obj["title"].toString();

        result.insert(groupName, groupId);
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

        /*                                        *
         *      Changing yyyy.MM.dd to dd.MM.yyyy
         *                                        */
        QStringList dateList = date.split(".");
        date = QDate(dateList[0].toInt(), dateList[1].toInt(), dateList[2].toInt()).toString("dd.MM.yyyy");

        QString resultString = "[" + dayOfWeekString + "] "         +
                discipline + " - " + date + "\n"                    +
                " - " + kindOfWork + "\n"                          +
                " - " + beginLesson + " - " + endLesson + "\n"     +
                " - " + lecturer;

        schedule.append(resultString);
    }
    return schedule;
}
