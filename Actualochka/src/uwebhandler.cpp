#include "include/System/uwebhandler.hpp"

UWebHandler::UWebHandler(QObject *parent) : QObject(parent)
{

}

QNetworkAccessManager* UWebHandler::AccsessUrl(QString turl)
{
    QNetworkAccessManager *nam = new QNetworkAccessManager();
    QUrl url(turl);

    nam->get(QNetworkRequest(url));
    return nam;
}

void UWebHandler::ontimeout()
{

}
