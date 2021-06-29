#include "../include/System/contentfileio.hpp"
#include "include/General/general.hpp"

ContentFileIO::ContentFileIO(QString filePath)
{
    _contentFile = new QFile(filePath);
    open();
}

ContentFileIO::~ContentFileIO()
{
    _contentFile->close();
    delete _contentFile;
}

ContentFile ContentFileIO::extractContent()
{
    open();

    ContentFile content;
    if (!_contentFile->isOpen())
    {
        content.Actualochka = content.ScheduleWeek = "Content file not opened to read";
        qWarning(logWarning()) << " [" << __FUNCTION__ << "] --- " << content.Actualochka;
        return content;
    }


    close();
    return content;
}

qint16 ContentFileIO::saveContent(ContentFile content)
{
    open();
    QJsonObject jsonObject;

    if (!_contentFile->isOpen())
    {
        qWarning(logWarning()) << " [" << __FUNCTION__ << "] --- " << "Content file not opened to save";
        return -1;
    }

    jsonObject["Actualochka"] = content.Actualochka;
    jsonObject["Schedule-Week"] = content.ScheduleWeek;

    _contentFile->write(QJsonDocument(jsonObject).toJson(QJsonDocument::Indented));

    close();
    return 0;
}

void ContentFileIO::saveContent(QString &tAct, QString &tSchWeek, CellData &tSchMonth)
{
    ContentFile content { tAct, tSchWeek, tSchMonth };
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

QJsonObject ContentFileIO::getActualochka()
{

}


QString ContentFileIO::Path = "C:\\ProgramData\\Actualochka\\content.json";
