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
    //this->Exec_PWD();
    //GetDirsInfo();
    return true;
}
/**
  *ReceiveMessage can receive one message once. one message = StatusCode + ' '...
  */

/*
void Client::Login()
{

}

void Client::GetDirsInfo()
{
    Exec_PASV();

    if(!this->SendMessage("CLNT \r\n"))
        return;
    if(!ReceiveMessage())
        return;
    if(!SendMessage("OPTS UTF8 ON\r\n"))
        return;
    if(!ReceiveMessage())
        return;
    Exec_LIST();
}

//FORMAT: USER
void Client::Exec_USER(QString name)
{
    if(!SendMessage("USER " + name + "\r\n"))
        return;
    if(!ReceiveMessage())
        return;
}
//FORMAT: PASS
*/
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
/*
//FORMAT:PASV
void Client::Exec_PASV()
{
    if(!SendMessage("PASV\r\n"))
        return;

    if(!ReceiveMessage())
        return;

    QStringList sub = CMD.split('(')[1].split(',');
    int a[6];
    for(int i = 0; i < sub.length() - 1; i ++)
    {
        a[i] = sub.at(i).toInt();
    }
    a[5] = sub.at(5).split(')').at(0).toInt();

    QString ip = QString::number(a[0])+ "."+ QString::number(a[1])+"." + QString::number(a[2])+"." + QString::number(a[3]);
    this->datasocket.connectToHost(ip, a[4] * 256 + a[5]);
}

void Client::Exec_PORT()
{

}

void Client::Exec_SYST()
{
    if(!SendMessage("SYST\r\n"))
        return;
    if(!ReceiveMessage())
        return;
}

void Client::Exec_TYPE()
{
    if(!SendMessage("TYPE I\r\n"))
        return;
    if(!ReceiveMessage())
        return;
}

void Client::Exec_LIST()
{
    QString str="LIST\r\n";
    if(!SendMessage(str))
        return;
    if(!ReceiveMessage())
        return;
    this->dirInfos.clear();
    while(this->datasocket.waitForReadyRead())
    {


            QByteArray array = this->datasocket.readAll();

            this->dirInfos.append(QString::fromUtf8(array));

    }
    this->datasocket.close();
    emit DirInfoUpdated();
     if(!ReceiveMessage())
         return;



}

void Client::Exec_RETR(QString path, QString filename)
{
    if(!SendMessage("RETR " + filename + "\r\n"))
        return;
    if(!ReceiveMessage())
        return;
    this->path = path;
    this->name = filename;
    //FileThread * thread = new FileThread(NULL, this);
    //this->datasocket.moveToThread(thread);
    //thread->start();


}

void Client::Exec_STOR(QString path)
{
    QStringList lists = path.split('/');
    if(!SendMessage("STOR " + lists.at(lists.length() - 1) + "\r\n"))
        return;
     if(!ReceiveMessage())
         return;
    if(this->StatusCode == 150)
    {
        bool flag = this->datasocket.waitForConnected();
        if(flag)
        {
            QFile file(path);
            file.open(QIODevice::ReadOnly);
            while(!file.atEnd())
            {
                QByteArray buf = file.read(1000);
                this->datasocket.write(buf);
                this->datasocket.waitForBytesWritten();
            }
            this->datasocket.close();
        }
        if(!ReceiveMessage())
            return;
    }
}

void Client::Exec_DELE()
{

}

void Client::Exec_MKD()
{

}

void Client::Exec_RMD()
{

}

void Client::Exec_SIZE()
{

}

void Client::Exec_RNFR()
{

}

void Client::Exec_RNTO()
{

}

void Client::Exec_QUIT()
{

}

void Client::Exec_HELP()
{

}

void Client::Exec_CWD(QString dir)
{
    QString path = this->CurrentPath + dir;
    if(!SendMessage("CWD " + path + "\r\n"))
        return;
    if(!ReceiveMessage())
        return;
    this->CurrentPath = path + "/";
}

void Client::Exec_PWD()
{
    if(!SendMessage("PWD\r\n"))
        return;
    if(!ReceiveMessage())
        return;
    int first = CMD.indexOf('\"');
    int end = CMD.indexOf("\"", first + 1);
    this->root = CMD.mid(first + 1, end - first - 1);
    this->CurrentPath = this->root;
}

void Client::LogOut()
{
    this->addr.clear();
    this->port = 0;
    this->buffer.clear();
    this->root.clear();
    this->CMD.clear();
    this->CurrentPath.clear();
    this->socket.close();
    this->datasocket.close();
}

void Client::UploadFile(QString path)
{
    this->Exec_PASV();
    this->Exec_STOR(path);

}

void Client::SaveAs(QString path, QString filename)
{
    Exec_PASV();
    Exec_RETR(path, filename);
}
*/
