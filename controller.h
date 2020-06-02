#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QTextStream>
#include "filethread.h"
#include <iostream>
#include <QDebug>
#include <client.h>
#include "filelistmodel.h"

class Controller
{
private:
    Client *client;
    FileListModel *model;
public:
    Controller();
    void connect(const QString &login, const QString &pass);
    ~Controller();
    FileListModel* getModel(){ return model; }
};

#endif // CONTROLLER_H
