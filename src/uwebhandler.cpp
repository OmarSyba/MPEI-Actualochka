#include "include/System/uwebhandler.hpp"

UWebHandler::UWebHandler(QObject *parent) :
    QObject(parent)
{

}

QNetworkAccessManager* UWebHandler::accsessUrl(QString turl)
{
    QNetworkAccessManager *nam = new QNetworkAccessManager();
    QUrl url(turl);

    nam->get(QNetworkRequest(url));
    return nam;
}

void UWebHandler::makeRequest(std::initializer_list<QString> tList)
{
    QStringList list(4);
    std::copy(tList.begin(), tList.end(), list.begin());

    auto namActuallity = accsessUrl(list.at(0));
    auto namScheduleWeek = accsessUrl(list.at(1));
    auto namMonth = accsessUrl(list.at(2));
    auto namGroups = accsessUrl(list.at(3));

    connect(namActuallity, &QNetworkAccessManager::finished, this, &UWebHandler::onResultActuallity);
    connect(namScheduleWeek, &QNetworkAccessManager::finished, this, &UWebHandler::onResultScheduleWeek);
    connect(namMonth, &QNetworkAccessManager::finished, this, &UWebHandler::onResultScheduleMonth);
    connect(namGroups, &QNetworkAccessManager::finished, this, &UWebHandler::onResultListOfGroups);

    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << list.at(1);
}

void UWebHandler::onResultActuallity(QNetworkReply *reply)
{
    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Get result actuallity";
    QString act = reply->error() == QNetworkReply::NoError ?
                ServerJsonParser::ParseJsonFromServer(reply, EReply_Type::Actualochka).at(0) :
                reply->errorString();

    reply->deleteLater();
    emit actuallity(act);
}

void UWebHandler::onResultScheduleWeek(QNetworkReply *reply)
{
    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Get result schedule";
    QStringList schedule = reply->error() == QNetworkReply::NoError ?
                ServerJsonParser::ParseJsonFromServer(reply, EReply_Type::ScheduleWeek):
                QVector<QString>(reply->errorString());

    reply->deleteLater();
    emit scheduleweek(schedule);

    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Schedule reply finished";
}

void UWebHandler::onResultScheduleMonth(QNetworkReply *reply)
{
    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Get result schedule month";
    QVector<CellData> scheduleMonth;

    if (reply->error() == QNetworkReply::NoError)
    {
        scheduleMonth = ServerJsonParser::ParseJsonMonth(reply);
    }

    reply->deleteLater();
    emit schedulemonth(scheduleMonth);

    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Schedule month reply finished";
}

void UWebHandler::onResultListOfGroups(QNetworkReply *reply)
{
    QMap<QString, quint32> groups;

    if (reply->error() == QNetworkReply::NoError)
    {
        groups = ServerJsonParser::ParseGroups(reply);
    }

    reply->deleteLater();
    emit listgroups(groups);

    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Group list reply finished";
}
