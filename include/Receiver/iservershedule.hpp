#ifndef ISERVERSHEDULE_HPP
#define ISERVERSHEDULE_HPP

#include <QObject>
#include <QJsonObject>

class IServerShedule : public QObject
{
    Q_OBJECT
public:
    virtual QJsonObject *GetShedule() = 0;
    virtual QString ParseJsonShedule(QJsonObject *) = 0;
};

#endif // ISERVERSHEDULE_HPP
