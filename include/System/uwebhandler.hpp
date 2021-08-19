#ifndef UWEBHANDLER_HPP
#define UWEBHANDLER_HPP

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include "include/General/general.hpp"
#include "include/System/serverjsonparser.hpp"

class IActuallityHandler
{
public:
    virtual void makeRequest(std::initializer_list<QString> tList) = 0;
    virtual void makeRequestProfile(QString tLogin, QString tPassword) = 0;
};

class UWebHandler : public QObject, public IActuallityHandler
{
    Q_OBJECT
public:
    explicit UWebHandler(QObject *parent = nullptr);

    QNetworkAccessManager* accsessUrl(QString url);
    void makeRequest(std::initializer_list<QString> tList) override;
    void makeRequestProfile(QString tLogin, QString tPassword) override;

public slots:
    void onResultActuallity(QNetworkReply *reply);
    void onResultScheduleWeek(QNetworkReply *reply);
    void onResultScheduleMonth(QNetworkReply *reply);
    void onResultListOfGroups(QNetworkReply *reply);

signals:
    void actuallity(QString tActuallity);
    void scheduleweek(QStringList tSchedule);
    void schedulemonth(QVector<CellData> tCellDatas);
    void listgroups(QMap<QString, quint32> tGroups);
};

#endif // UWEBHANDLER_HPP
