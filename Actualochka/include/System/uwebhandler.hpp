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

signals:

private:
    QNetworkAccessManager *manager = nullptr;
};

#endif // UWEBHANDLER_HPP
