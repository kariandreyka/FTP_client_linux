#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle("Log in");
}

Login::~Login()
{
    delete ui;
}


void Login::on_pushButton_clicked()
{
    if(ui->lineEdit->text() != ""){
        if(ui->lineEdit_2->text() != ""){
            this->password = ui->lineEdit_2->text();
            this->ip = ui->lineEdit->text();
            emit this->valueChanged();
        }
    }
}

QString Login::getIP(){
    return this->ip;
}

QString Login::getPassword(){
    return this->password;
}
