#ifndef TREE_H
#define TREE_H

#include <QTreeView>
#include <QObject>

class Tree : public QTreeView
{
    Q_OBJECT
public:
    explicit Tree(QWidget *parent = 0);
};

#endif // TREE_H
