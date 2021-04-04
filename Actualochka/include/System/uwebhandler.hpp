#ifndef UWEBHANDLER_HPP
#define UWEBHANDLER_HPP

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class UWebHandler : public QObject
{
    Q_OBJECT
public:
    explicit UWebHandler(QObject *parent = nullptr);

    QNetworkAccessManager* AccsessUrl(QString url);
};

#endif // UWEBHANDLER_HPP
