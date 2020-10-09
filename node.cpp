#include "node.h"

Node::Node(const QString &s, Node *parent) : data(s), parent(parent)
{

}

Node::~Node()
{
    qDeleteAll(children);
    children.clear();
}

Node *Node::child(int row)
{
    return children.value(row);
}

int Node::childNumber() const
{
    if (parent) {
        return parent->children.indexOf(const_cast<Node*>(this)); // this по опр не конст, поэтому преобразование (?)
    }
    return 0;
}

QString Node::getData() const
{
    return data;
}

Node *Node::getParent() const
{
    return parent;
}

int Node::childrenCount() const
{
    return children.size();
}

Node *Node::insertNode(int pos)
{
    if (pos<0 || pos >children.size()) return 0;

    Node *node = new Node(QString(), this); // создали узел дочерн для текущего
    children.insert(pos, node); // и вставили

    return node;
}

bool Node::insert(int pos, int count)
{
    if (pos<0 || pos >children.size()) return false;
    if (count<1) return false;
    for (int row=0; row<count; ++row) {
        Node *node = new Node(QString(), this); // создали узел дочерн для текущего
        children.insert(pos, node); // и вставили
    }
    return true;
}

bool Node::setData(const QString &s)
{
    if (data==s) return false;
    data = s;
    return true;
}

QString Node::getDataAsString(int nodeIndex, int parentIndex)
{
    if (parentIndex == 0)
        return QString("%1  # %2  #")
            .arg(nodeIndex)
            .arg(getData());

    return QString("%1  # %2  #  %3")
            .arg(nodeIndex)
            .arg(getData())
            .arg(parentIndex);
}
