#include "include/Mainwindow/mainwindow.hpp"
#include "include/General/general.hpp"
#include <QProcess>
#include <QStyleFactory>
#include <QApplication>

Q_LOGGING_CATEGORY(logDebug,    "Debug")
Q_LOGGING_CATEGORY(logInfo,     "Information")
Q_LOGGING_CATEGORY(logWarning,  "Warning")
Q_LOGGING_CATEGORY(logCritical, "Critical")
Q_LOGGING_CATEGORY(logFatal,    "Fatal")

void setUpAppclication(QApplication& app)
{
    app.setApplicationName("Actualochka");
    app.setApplicationVersion(act::CurrnetVersion);
    app.setOrganizationName("poor mpei students");
    app.setOrganizationDomain("mpei.space");
    app.setQuitOnLastWindowClosed(false);
    app.setStyle(QStyleFactory::create("Fusion"));
}

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    QTextStream out(gFile.data());
    out << QDateTime::currentDateTime().toString("[dd.MM.yyyy hh:mm:ss] ");

    switch (type)
    {
    case QtInfoMsg:     out << "INF";
        break;
    case QtDebugMsg:    out << "DBG";
        break;
    case QtWarningMsg:  out << "WRN";
        break;
    case QtCriticalMsg: out << "CRT";
        break;
    case QtFatalMsg:    out << "FTL";
        break;
    }

    out << " " << context.category << " : " << msg << "\n";
    out.flush();
}

void setUpStyleApp(QApplication& app, bool isDark)
{
    QString stylePath = isDark ? ":qdarkstyle/style.qss" : ":qlightstyle/style.qss";

    QFile file(stylePath);
    if (!file.exists())
    {
        qCritical(logCritical()) << " [" << __FUNCTION__ << "] --- " << "Can't get style resources " << stylePath
                                 << " " << file.errorString();
        return;
    }
    file.open(QFile::ReadOnly | QFile::Text);

    QTextStream stream(&file);
    app.setStyleSheet(stream.readAll());
    file.close();

    qInfo(logInfo()) << " [" << __FUNCTION__ << "] --- " << "Style changed" << stylePath;
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    setUpAppclication(a);
    gFile.reset(new QFile("C:/ProgramData/Actualochka/log.txt"));
    gFile.data()->open(QFile::Append | QFile::Text);
    qInstallMessageHandler(messageHandler);

    qInfo(logInfo()) << "\n\n\n\t\t*** Start Application at " << QDateTime::currentDateTime() << " ***\n";

    /* **************************************************************
     *          Изменить белый на бледный + календарь не изменяется
     * ************************************************************* */
    //setUpStyleApp(a);

    MainWindow w;
    QObject::connect(&w, &MainWindow::quitapp, &a, &QApplication::quit);
    QObject::connect(&w, &MainWindow::newversion, [&]()
    {
        QProcess P;
        QString Path = QString(QDir().currentPath() + "/maintenancetool.exe");
        P.start(Path);
    });

    return a.exec();
}
