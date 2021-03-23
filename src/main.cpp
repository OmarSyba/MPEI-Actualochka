#include "include/Mainwindow/mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Actualochka Getter");
    MainWindow w;

    a.setQuitOnLastWindowClosed(false);

    return a.exec();
}
