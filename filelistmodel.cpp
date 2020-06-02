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
         item->setWhatsThis("FOLDER");
         return item;
    }
    else{
        QStandardItem *item = new QStandardItem();
        item->setIcon(QIcon(":/img/images/file.jpeg"));
        item->setText(name);
        item->setWhatsThis("FILE");
        return item;
    }
}

void FileListModel::setFileList(std::vector<std::string> &fileList){
    this->clear();
    QList<QStandardItem*> files;
    QList<QStandardItem*> folders;
    foreach (std::string file, fileList) {
        QStandardItem *item = this->createItem(QString::fromUtf8(file.c_str()));
        if(item->whatsThis() == "FOLDER"){
            folders.push_back(item);
        }
        else{
            files.push_back(item);
        }

        //this->setItem(0, this->Files.back());
    }
    folders.append(files);
    this->appendColumn(folders);
}


