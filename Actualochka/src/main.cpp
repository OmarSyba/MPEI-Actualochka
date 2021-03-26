#include "include/Mainwindow/mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Actualochka Getter");
    a.setQuitOnLastWindowClosed(false);
    MainWindow w;

    QObject::connect(&w, &MainWindow::ForceClose, &a, &QApplication::quit);
    return a.exec();
}
