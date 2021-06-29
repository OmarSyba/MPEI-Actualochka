#ifndef CONTENTFILEIO_HPP
#define CONTENTFILEIO_HPP

#include <QFile>

class ContentFileIO
{
public:
    ContentFileIO(QString filePath = Path);
    ~ContentFileIO();

    QString extcractContent() const;

    void open();
    void close();

private:

private:
    static QString Path;
    QFile *_contentFile = nullptr;
};

#endif // CONTENTFILEIO_HPP
