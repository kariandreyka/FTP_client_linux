#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDebug>

class FileListModel : QStandardItemModel
{
    Q_OBJECT
private:
    QString folderIcon = ":images/folder.png";
    QString fileIcon = ":images/file.jpeg";
public:
    explicit FileListModel(QObject *parent = nullptr);
    void setFileList(std::vector<std::string> &fileList);
    QStandardItem* createItem(const QString &name);
};

#endif // FILELISTMODEL_H
