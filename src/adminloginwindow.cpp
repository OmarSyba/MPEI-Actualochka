#include "include/Mainwindow/adminloginwindow.hpp"
#include "ui_adminloginwindow.h"

AdminLogInWindow::AdminLogInWindow(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::AdminLogInWindow)
{
    ui->setupUi(this);
    ui->lineEditPassword->setEchoMode(QLineEdit::EchoMode::Password);

    //TODO override exec, make acceptUser login

    connect(ui->pushButtonCancel, &QPushButton::clicked, [&]()
    {
        reject();
    });

    connect(ui->pushButtonUser, &QPushButton::clicked, [&]()
    {
        emit acceptUser();
    });

    connect(ui->pushButtonLogin, &QPushButton::clicked, [&]()
    {
        _login = ui->lineEditLogin->text();
        _password = ui->lineEditPassword->text();
    });
}


AdminLogInWindow::~AdminLogInWindow()
{
    delete ui;
}

const QString &AdminLogInWindow::login() const
{
    return _login;
}

const QString &AdminLogInWindow::password() const
{
    return _password;
}
