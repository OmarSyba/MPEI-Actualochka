#include "include/Mainwindow/adminloginwindow.hpp"
#include "ui_adminloginwindow.h"

AdminLogInWindow::AdminLogInWindow(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::AdminLogInWindow)
{
    ui->setupUi(this);
    ui->lineEditPassword->setEchoMode(QLineEdit::EchoMode::Password);
    setWindowTitle(tr("Вход в приложение"));
    setMinimumSize(QSize(640, 480));

    //TODO override exec, make acceptUser login

    connect(ui->pushButtonCancel, &QPushButton::clicked, [&]()
    {
        setResult(DialogCode::Rejected);
        reject();
    });

    connect(ui->pushButtonUser, &QPushButton::clicked, [&]()
    {
        setResult(DialogCode::UserAccepted);
        QDialog::done(DialogCode::UserAccepted);
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

int AdminLogInWindow::exec()
{
    return QDialog::exec();
}

void AdminLogInWindow::acceptUser()
{
    setResult(DialogCode::UserAccepted);
}
