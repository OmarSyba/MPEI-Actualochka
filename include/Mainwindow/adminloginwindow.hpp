#ifndef ADMINLOGINWINDOW_HPP
#define ADMINLOGINWINDOW_HPP

#include <QDialog>

namespace Ui {
class AdminLogInWindow;
}

class AdminLogInWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AdminLogInWindow(QDialog *parent = nullptr);

    enum DialogCode { Rejected, Accepted, UserAccepted };
    ~AdminLogInWindow();

    const QString &login() const;
    const QString &password() const;

Q_SIGNALS:
    void acceptedUser();

public Q_SLOTS:
    virtual int exec() override;
    void acceptUser();

private:
    QString _login;
    QString _password;

    Ui::AdminLogInWindow *ui;
};

#endif // ADMINLOGINWINDOW_HPP
