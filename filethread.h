#ifndef FILETHREAD_H
#define FILETHREAD_H
#include "basethreadclass.h"
//#include "controller.h"
#include "client.h"
#include <QFile>

class FileThread : public BaseThreadClass
{
private:
    Client *client;
    char buf[100];
public:
    FileThread(QObject *parent = nullptr, Client *c = nullptr);
    void run() override;
    ~FileThread(){ delete client; }
};

#endif // FILETHREAD_H
