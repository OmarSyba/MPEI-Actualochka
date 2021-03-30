#include "include/System/uwebhandler.hpp"

UWebHandler::UWebHandler(QObject *parent) : QObject(parent)
{

}

QNetworkAccessManager* UWebHandler::AccsessUrl(QString turl, void (&onResult)(QNetworkReply *))
{
    QNetworkAccessManager *nam = new QNetworkAccessManager();
    QUrl url(turl);

    nam->get(QNetworkRequest(url));

    nam->deleteLater();
    return nam;
}

void UWebHandler::ontimeout()
{

}
