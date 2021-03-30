#include "include/Mainwindow/mainwindow.hpp"

#include <QProcess>
#include <QApplication>

int main(int argc, char *argv[])
{
    if (!QDir(logdir).exists())
    {
        QDir actDir("C:/ProgramData");
        actDir.mkdir("Actualochka");
    }

    QApplication a(argc, argv);
    a.setApplicationName("Actualochka");
    a.setApplicationVersion(act::CurrnetVersion);
    a.setOrganizationName("poor mpei students");
    a.setOrganizationDomain("mpei.space");
    a.setQuitOnLastWindowClosed(false);
    MainWindow w;

    QObject::connect(&w, &MainWindow::quitapp, &a, &QApplication::quit);
//    QObject::connect(&w, &MainWindow::FoundedNewVersion, [&]()
//    {
//        QProcess P(&w);
//        QString Path = QString(QDir().currentPath() + "/maintenancetool.exe");
//        P.start(Path);
//        P.waitForFinished(-1);
//    });
    return a.exec();
}
