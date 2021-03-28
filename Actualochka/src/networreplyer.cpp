#include "../include/Receiver/networreplyer.hpp"

NetworkReplyer::NetworkReplyer() = default;

QNetworkAccessManager *NetworkReplyer::AccessUrl(QString turl) noexcept
{
    QNetworkAccessManager* nam = new QNetworkAccessManager();

    QUrl url(turl);
    nam->get(QNetworkRequest(url));

    return nam;
}
