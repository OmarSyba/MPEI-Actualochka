#ifndef SERVERJSONPARSER_HPP
#define SERVERJSONPARSER_HPP

#include <QObject>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

enum IEType
{
    Schedule = 0,
    Actualochka = 1
};

struct CellData
{
    QDateTime date;
    QString lessionType;
    QString lession;
};

class ServerJsonParser : public QObject
{
    Q_OBJECT
public:
    ServerJsonParser() = delete;

    static QVector<QString> ParseJsonFromServer(QNetworkReply *reply, IEType type);
    static QVector<CellData> ParseJsonMonth(QNetworkReply *reply);
private:
    static QVector<QString> ParseJson(QJsonArray& tjsonArray);
};

#endif // SERVERJSONPARSER_HPP
