#ifndef ISERVERACTUALOCHKA_H
#define ISERVERACTUALOCHKA_H

#include <QObject>
#include <QJsonObject>

class IServerActualochka : public QObject
{
    Q_OBJECT
public:
    virtual QJsonObject *GetActualocha() = 0;
    virtual QString ParseActualochka(QJsonObject *) = 0;
};

#endif // ISERVERACTUALOCHKA_H
