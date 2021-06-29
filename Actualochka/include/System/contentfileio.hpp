#ifndef CONTENTFILEIO_HPP
#define CONTENTFILEIO_HPP

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "include/General/general.hpp"

struct ContentFile
{
    QString Actualochka;
    QString ScheduleWeek;
    CellData ScheduleMonth;
};

class ContentFileIO
{
public:
    ContentFileIO(QString filePath = Path);
    ~ContentFileIO();

    ContentFile extractContent();
    qint16 saveContent(ContentFile file);
    void saveContent(QString &tAct, QString &tSchWeek, CellData &tSchMonth);

private:
    void open();
    void close();

    QJsonObject getActualochka();
    QJsonObject getScheduleWeek();
    QJsonObject getScheduleMonth();

private:
    static QString Path;
    QFile *_contentFile = nullptr;
};

#endif // CONTENTFILEIO_HPP
