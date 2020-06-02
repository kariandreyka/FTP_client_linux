#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    QString getIP();
    QString getPassword();

signals:
    void valueChanged();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Login *ui;
    QString ip;
    QString password;
};

#endif // LOGIN_H
