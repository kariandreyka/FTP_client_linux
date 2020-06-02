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

#include<sys/sendfile.h>
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
    void clearBuffer();
    std::string loginPassword;
    char *file;

public:
    QString path;
    QString fileName;


    bool InitConnect(QString ip, int port, QString pass);
    int getSocket(){ return this->sock; }

    void Exec_PASS(QString pass);
    std::vector<std::string> Exec_ls();
    void Exec_get(QString path, QString fileName);

    void Exec_cd(QString dirName);
    void Exec_qiut();

public:

    QString Message;
    bool IsConnect;

    void Connect();
    void Error(QString error);

};
#endif // CLIENT_H

