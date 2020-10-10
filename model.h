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

    QStringList getData() const;

    void moveUp(const QModelIndex &indexToMove);
    void moveDown(const QModelIndex &indexToMove);

    Node *getNodeFromIndex (const QModelIndex &index) const;

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

    virtual bool insertRows(int row, int count, const QModelIndex &parent) override;
    virtual bool removeRows(int row, int count, const QModelIndex &parent) override;

private:
    void processNode(Node *node, QStringList &list, int &nodeIndex) const;
    Node  *rootNode; //



};

#endif // MODEL_H
