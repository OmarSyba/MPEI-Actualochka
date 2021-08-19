#include "../include/System/contentfileio.hpp"
#include "include/General/general.hpp"

ContentFileIO::ContentFileIO(QString filePath)
{
    _contentFile = new QFile(filePath);
}

ContentFileIO::~ContentFileIO()
{
    _contentFile->close();
    delete _contentFile;
}

Content ContentFileIO::extractContent()
{
    open();

    Content content;
    if (!_contentFile->isOpen())
    {
        content.Actuallity = "Content file not opened to read";
        qWarning(logWarning()) << " [" << __FUNCTION__ << "] --- " << content.Actuallity;
        return content;
    }

    QJsonObject object = QJsonDocument::fromJson(_contentFile->readAll()).object();
    content.Actuallity = getActualochka(object);
    content.ScheduleWeek = getScheduleWeek(object);
    content.ScheduleMonth = getScheduleMonth(object);

    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << content.Actuallity;

    close();
    return content;
}

qint16 ContentFileIO::saveContent(Content content)
{
    open();
    QJsonObject jsonObject;

    if (!_contentFile->isOpen())
    {
        qWarning(logWarning()) << " [" << __FUNCTION__ << "] --- " << "Content file not opened to save";
        return -1;
    }

    QJsonArray arrayWeek;
    QJsonArray arrayMonth;

    for (auto& scheduleWeek : content.ScheduleWeek)
    {
        arrayWeek.append(scheduleWeek);
    }

    for (auto& cellData : content.ScheduleMonth)
    {
        arrayMonth.append(cellData.date.toString()
                     + "::" + cellData.lession
                     + "::" + cellData.lessionType);
    }

    jsonObject["Actualochka"] = content.Actuallity;
    jsonObject["Schedule-Week"] = arrayWeek;
    jsonObject["Schedule-Month"] = arrayMonth;

    _contentFile->write(QJsonDocument(jsonObject).toJson(QJsonDocument::Indented));

    close();
    return 0;
}

void ContentFileIO::saveContent(QString &tAct, QVector<QString> &tSchWeek, QVector<CellData> &tSchMonth)
{
    Content content { tAct, tSchWeek, tSchMonth };
    saveContent(content);
}

void ContentFileIO::open()
{
    if (!_contentFile->open(QIODevice::ReadWrite))
    {
        qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Open content file";
    }
}

void ContentFileIO::close()
{
    _contentFile->close();
}

QString ContentFileIO::getActualochka(QJsonObject tObj)
{
    return tObj["Actualochka"].toString();
}

QVector<QString> ContentFileIO::getScheduleWeek(QJsonObject tObj)
{
    QJsonArray schArray = tObj["Schedule-Month"].toArray();
    QVector<QString> schedule;

    for (QJsonValue x : schArray)
    {
        schedule.append(x.toString());
    }

    return schedule;
}

QVector<CellData> ContentFileIO::getScheduleMonth(QJsonObject tObj)
{
    QJsonArray schArray = tObj["Schedule-Month"].toArray();
    QVector<CellData> schedule;

    for (QJsonValue x : schArray)
    {
        CellData data;
        QString stringValue = x.toString();
        QStringList list = stringValue.split("::");

        data.date = QDateTime::fromString(list.at(0));
        data.lession = list.at(1);
        data.lessionType = list.at(2);

        schedule.append(data);
    }

    return schedule;
}


QString ContentFileIO::Path = "C:\\ProgramData\\Actualochka\\content.json";
