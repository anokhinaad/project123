#ifndef NODE_H
#define NODE_H

#include <QString>
#include <QList>

class Node
{
public:
    Node(const QString &s, Node *parent=0);
    ~Node();
    Node *child(int row);

    int childNumber() const;

    QString getData() const;
    Node *getParent() const;
    int childrenCount() const;

    Node *insertNode(int pos);
    bool removeNodes(int row, int count);

    bool moveNode(int from, int to);

    bool takeNode(int row);
    bool insertNode(int pos, Node *node);

    bool insert(int pos, int count); // позиция и кол-во доч элем
    bool setData(const QString &s);

    QString getDataAsString(int nodeIndex, int parentIndex);


private:
    QString data;
    Node *parent;
    QList<Node*> children;
};

#endif // NODE_H
