#ifndef NETWORREPLYER_HPP
#define NETWORREPLYER_HPP

#include "../General/general.hpp"

#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

class NetworkReplyer : public QObject
{
    Q_OBJECT
    NetworkReplyer(NetworkReplyer&&) = delete;
    NetworkReplyer(const NetworkReplyer&) = delete;
public:
    NetworkReplyer();
    static QNetworkAccessManager *AccessUrl(QString url) noexcept;
};

#endif // NETWORREPLYER_HPP
