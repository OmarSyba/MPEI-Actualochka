#include "../include/Receiver/networreplyer.hpp"

QNetworkAccessManager *NetworReplyer::AccessUrl(QString turl) noexcept
{
    QNetworkAccessManager* nam = new QNetworkAccessManager();

    QUrl url(turl);
    nam->get(QNetworkRequest(url));

    return nam;
}
