#include "filelistmodel.h"

FileListModel::FileListModel(QObject *parent) : QStandardItemModel(parent)
{

}

QStandardItem* FileListModel::createItem(const QString &name){
    QStringList items = name.split(".");
    if(items.length() == 1){
         QStandardItem *item = new QStandardItem();
         item->setIcon(QIcon(":/img/images/folder.png"));
         item->setText(name);
         return item;
    }
    else{
        QStandardItem *item = new QStandardItem();
        item->setIcon(QIcon(":/img/images/file.jpeg"));
        item->setText(name);
        return item;
    }
}

void FileListModel::setFileList(std::vector<std::string> &fileList){
    this->clear();
    foreach (std::string file, fileList) {
        qDebug() << "hello fucker";
        this->Files.push_back(this->createItem(QString::fromUtf8(file.c_str())));
        //this->setItem(0, this->Files.back());
    }
    this->appendColumn(this->Files);
}


