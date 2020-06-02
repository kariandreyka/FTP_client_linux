#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    controller = new Controller();
    ui->setupUi(this);
    this->login = new Login();
    login->show();
    ui->listView->setModel((QAbstractItemModel*)(this->controller->getModel()));
    QObject::connect(this->login, SIGNAL(valueChanged()), this, SLOT(init()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete login;
    delete controller;
}

void MainWindow::init(){
    controller->connect(this->login->getIP(), this->login->getPassword());
    login->hide();
    this->show();
}
