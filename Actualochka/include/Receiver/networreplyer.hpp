#ifndef NETWORREPLYER_HPP
#define NETWORREPLYER_HPP

#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

class NetworReplyer
{
    NetworReplyer() = delete;
    NetworReplyer(NetworReplyer&&) = delete;
    NetworReplyer(const NetworReplyer&) = delete;
public:
    static QNetworkAccessManager *AccessUrl(QString url) noexcept;
};

#endif // NETWORREPLYER_HPP
