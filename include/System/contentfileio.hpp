#ifndef CONTENTFILEIO_HPP
#define CONTENTFILEIO_HPP

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "include/General/general.hpp"

class ContentFileIO
{
public:
    ContentFileIO(QString filePath = Path);
    ~ContentFileIO();

    Content extractContent();
    qint16 saveContent(Content file);
    void saveContent(QString &tAct, QVector<QString> &tSchWeek, QVector<CellData> &tSchMonth);

private:
    void open();
    void close();

    QString getActualochka(QJsonObject tObj);
    QVector<QString> getScheduleWeek(QJsonObject tObj);
    QVector<CellData> getScheduleMonth(QJsonObject tObj);

private:
    static QString Path;
    QFile *_contentFile = nullptr;
};

#endif // CONTENTFILEIO_HPP
