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

    QJsonArray arrayMonth;
    QJsonArray arrayWeek;

    for (auto& cellData : content.ScheduleMonth)
    {
        arrayMonth.append(cellData.date.toString()
                     + "::" + cellData.lession
                     + "::" + cellData.lessionType);
    }

    for (auto& scheduleWeek : content.ScheduleWeek)
    {
        arrayWeek.append(scheduleWeek);
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

// TODO

QJsonObject ContentFileIO::getActualochka()
{

}

QJsonObject ContentFileIO::getScheduleWeek()
{

}

QJsonObject ContentFileIO::getScheduleMonth()
{

}


QString ContentFileIO::Path = "C:\\ProgramData\\Actualochka\\content.json";
