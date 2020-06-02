#include "filethread.h"

FileThread::FileThread(QObject *parent, Client *c) : BaseThreadClass(parent)
{
    this->client = client;
}

void FileThread::run(){
    QFile file(this->client->path);
    file.open(QIODevice::WriteOnly);
    char *f;
    int size;
    recv(this->client->getSocket(), &size, sizeof (int), 0);
    f = (char*)malloc(size);
    recv(this->client->getSocket(), f, size, 0);
    file.write(f, size);

}
