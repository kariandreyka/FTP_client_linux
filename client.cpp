#include "client.h"
#include <exception>
#include <iostream>
#include <QStringList>
#include <QTextCodec>
#include <fstream>
#include <QFile>
#include "filethread.h"

using namespace std;

Client::Client()
{
    this->IsConnect = false;
}

bool Client::InitConnect(QString _ip, int _port, QString pass)
{

    this->LoginPassword = pass.toUtf8().constData();
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    this->server.sin_family = AF_INET;
    this->server.sin_port = htons(1304);
    this->server.sin_addr.s_addr = inet_addr(_ip.toUtf8().constData());
    int k = connect(sock,(struct sockaddr*)&server, sizeof(server));
    if(k == -1)
      {
        qDebug() << "can't connect socket";
        return false;
      }
    Exec_PASS(pass);
    this->IsConnect = true;
    return true;
}

void Client::Exec_PASS(QString pass)
{
    recv(this->sock, this->buffer, 100, 0);
    this->clearBuffer();
    std::strcpy(buffer, std::string(pass.toUtf8().constData()).c_str());
    send(this->sock, this->buffer, 100, 0);

}

void Client::clearBuffer(){
    memset(this->buffer, 0, 100);
}

std::vector<std::string> Client::Exec_ls(){
    this->clearBuffer();
    std::strcpy(this->buffer, "ls");
    send(this->sock, this->buffer, 100, 0);
    int size = 0;
    recv(this->sock, &size, sizeof(int), 0);
    this->file = (char*)malloc(size);
    recv(this->sock, this->file, size, 0);

    std::vector<std::string> fileNames;
    std::string token;
    std::string buffString = this->file;
    std::istringstream fileNameStream(buffString);

    while(std::getline(fileNameStream, token, '\n')){
        fileNames.push_back(token);
    }

    return fileNames;
}

void Client::Exec_get(QString path, QString fileName){
    this->clearBuffer();
    this->path = path;
    this->name = fileName;
    std::strcpy(this->buffer, "get ");
    std::strcat(this->buffer, std::string(fileName.toUtf8().constData()).c_str());
    send(this->sock, this->buffer, 100, 0);
    FileThread *thread = new FileThread(nullptr, this);
    thread->run();
}

void Client::Exec_cd(QString dirName){
    std::strcpy(this->buffer, "cd ");
    std::strcat(this->buffer, std::string(dirName.toUtf8().constData()).c_str());
    send(this->sock, this->buffer, 100, 0);
    int status;
    recv(this->sock, &status, sizeof (int), 0);
    if(!status)
        return;
}

void Client::Exec_qiut(){
    std::strcpy(this->buffer, "quit");
    send(this->sock, this->buffer, 100, 0);
    int status;
    recv(sock, &status, 100, 0);

    if(status){
        qDebug() << "Server sucsessfully closed";
    }else
        qDebug() << "failed to close connection";

}
