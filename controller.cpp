#include "controller.h"

Controller::Controller()
{
    this->client = new Client();
    this->model = new FileListModel();
}

void Controller::connect(const QString &login, const QString &pass){
    int sucsess = this->client->InitConnect(login, 1304, pass);
    if(!sucsess){
        qDebug() << "connection error";
        return;
    }
    std::vector<std::string> fileList = this->client->Exec_ls();
    foreach (std::string file, fileList) {
       qDebug() << QString(file.c_str());
    }
    this->model->setFileList(fileList);
    this->client->Exec_qiut();
}

Controller::~Controller(){
    delete this->client;
    delete this->model;
}


