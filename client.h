#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sstream>

/*for getting file size using stat()*/
#include<sys/stat.h>

/*for sendfile()*/
#include<sys/sendfile.h>

/*for O_RDONLY*/
#include<fcntl.h>

#include <QString>

class Client
{
public:
    Client();
private:

    struct sockaddr_in server;
    int port;
    int sock;
    char buffer[100];
    char *file;
    std::string LoginPassword;
    int    StatusCode;//cur
    void clearBuffer();
//    QString root;
 //   QString CurrentPath;

public:
    bool InitConnect(QString ip, int port, QString pass);
    int getSocket(){ return this->sock; }
 /*   void Login();
    void LogOut();
    void UploadFile(QString path);
    void GetDirsInfo();
    void RetriveFile(QString str);
    void Receive_MSG();
    void SaveAs(QString path, QString filename);*/
public:
//    void Exec_USER(QString name);
    void Exec_PASS(QString pass);
 /*   void Exec_PASV();
    void Exec_PORT();
    void Exec_SYST();
    void Exec_CDUP();
    void Exec_TYPE();
    void Exec_LIST();
    void Exec_RETR(QString path, QString name);
    void Exec_STOR(QString path);
    void Exec_DELE();
    void Exec_MKD();
    void Exec_RMD();
    void Exec_SIZE();
    void Exec_RNFR();
    void Exec_RNTO();

    void Exec_HELP();
    void Exec_CWD(QString path);*/
    std::vector<std::string> Exec_ls();
    void Exec_get(QString path, QString fileName);
    void Exec_PWD();
    void Exec_cd(QString dirName);
    void Exec_qiut();

public:
    QString CMD; // cmd
//    QString dirInfos;
    QString Message;
    bool IsConnect;
    QString path;
    QString name;


    //void GetDirsInfo();

    void BufferUpdate();
    void MessageSended();
//    void DirInfoUpdated();
    void Connect();
//    void DisConnect();
//    void AtRoot();
    void Error(QString error);

};
#endif // CLIENT_H

