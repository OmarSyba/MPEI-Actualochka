#include "../include/Mainwindow/mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QThread>
#include <QKeyEvent>
#include <QCheckBox>
#include <QSettings>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitUiParams();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitUiParams()
{
    setWindowTitle(tr("Актуалочка"));
    setFixedSize(QSize(640, 480));
}

