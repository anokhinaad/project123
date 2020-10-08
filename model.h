#ifndef MODEL_H
#define MODEL_H

#include <QAbstractItemModel>
#include <QObject>
#include <node.h>

class Node;

class Model : public QAbstractItemModel
{
    Q_OBJECT
public:
    Model();
    void clearModel(); // очистка
    void setModel(const QStringList &lines); // заполнение данными из файла

    Node *getNodeFromIndex (const QModelIndex &index) const;

    // QAbstractItemModel interface
public:
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    Node  *rootNode; //

};

#endif // MODEL_H
