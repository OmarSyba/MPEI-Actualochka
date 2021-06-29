#include "../include/System/contentfileio.hpp"
#include "include/General/general.hpp"

ContentFileIO::ContentFileIO(QString filePath)
{
    _contentFile = new QFile(filePath);
    open();
}

ContentFileIO::~ContentFileIO()
{
    delete _contentFile;
}

QString ContentFileIO::extcractContent() const
{
    QString result;
    if (!_contentFile->isOpen())
    {
        result = "Content file doesn't opened";
        qWarning(logWarning()) << " [" << __FUNCTION__ << "] --- " << result;
        return result;
    }

    //res
}

void ContentFileIO::open()
{
    if (!_contentFile->open(QIODevice::WriteOnly))
    {
        qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Open content file";
    }
}

void ContentFileIO::close()
{
    _contentFile->close();
}


QString ContentFileIO::Path = "C:\\ProgramData\\Actualochka\\content.txt";
