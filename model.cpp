#include "model.h"
#include <node.h>
#include <QMessageBox>
#include <QMap>
#include <QtDebug>

Model::Model()
{
   rootNode = new Node("Root", 0);
}

void Model::clearModel()
{
    delete rootNode;
    rootNode = new Node("Root", 0);
}

void Model::setModel(const QStringList &lines) // принимает список строк данных и превращает в узлы
{
    beginResetModel();

    QMap<int, Node*> nodesMap;

    foreach (const QString &s, lines) // указатель избавляет от копий
    {
        QStringList list = s.split("#");
        const int listSize = list.size();

        if (listSize <=1) {
            QMessageBox::warning(0, "Ошибка в структуре данных",
                                 QString("Строка %1 имеет неподходящую структуру.\n"
                                         "Она будет пропущена.").arg(s));
            continue;
        }

        if (listSize == 2) {
            QMessageBox::warning(0, "Ошибка в структуре данных",
                                 QString("Строка %1 имеет неподходящую структуру.\n"
                                         "Будет предпринята обработка строки.").arg(s));
            // 3   #    1.1   Материал 1           1
            QStringList auxList = list.at(1).split(" ", QString::SkipEmptyParts);
            //получили 1.1|Материал|1|1
            if (auxList.size()>1) {
                QString potentialParentString = auxList.last();

                bool ok;
                int potentialParentNumber = potentialParentString.toInt(&ok);
                if (ok) {
                    list.append(potentialParentString);

                    auxList.takeLast();
                    QString dataString = auxList.join(" ");
                    list.replace(1, dataString);
                }
                else {
                    QMessageBox::warning(0, "Ошибка в структуре данных",
                                         "Не удалось обработать строку");
                    continue;
                }
            }
        }

        //обработка правильной строки

        QString nodeIndexString = list.first().simplified();
        if (nodeIndexString.length() > 6) {
            QMessageBox::warning(0, "Ошибка в структуре данных",
                                 "Слишком длинный индекс");
            continue;
        }

        int nodeIndex = nodeIndexString.toInt();
        QString data = list.at(1).trimmed();
        int parentIndex = list.at(2).simplified().toInt();

        //1. Если parentIndex == 0 -> записываем в корень
        if (parentIndex == 0) {
            Node *currentNode = rootNode->insertNode(rootNode->childrenCount());
            currentNode->setData(data);
            nodesMap.insert(nodeIndex, currentNode);
        }
        else {
            Node *parentNode = nodesMap.value(parentIndex, 0);
            if (!parentNode) {
                QMessageBox::warning(0, "Ошибка в структуре данных",
                                     "Не удалось обработать строку");
                continue;
            }

            Node *currentNode = parentNode->insertNode(parentNode->childrenCount());
            currentNode->setData(data);
            nodesMap.insert(nodeIndex, currentNode);
        }
    }
    endResetModel();
}

QStringList Model::getData() const
{
    QStringList result;

    int nodeIndex = 0;
    processNode(rootNode, result, nodeIndex);

    return result;
}

void Model::processNode(Node *node, QStringList &list, int &nodeIndex) const
{
    int parentIndex = nodeIndex;
    const int childrenCount = node->childrenCount();
    for (int i=0; i<childrenCount; ++i) {
        Node *n_i = node->child(i);
        QString currentNodePresentation = n_i->getDataAsString(++nodeIndex, parentIndex);
        list << currentNodePresentation;

        processNode(n_i, list, nodeIndex);
    }
}


QModelIndex Model::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0) return QModelIndex(); // только в 1 столбце существует

    //Node *parentNode = static_cast<Node*>(parent.internalPointer());
    Node *parentNode = getNodeFromIndex(parent);
    Node *childNode = parentNode->child(row); // дочерний элем под номером row

     // две ситуации - имеет и не имеет доч элем

    if (!childNode) return QModelIndex();

    return createIndex(row, column, childNode);

}

QModelIndex Model::parent(const QModelIndex &child) const
{
     QModelIndex result;
    if (!child.isValid()) return QModelIndex();

    // две ситуации: в глубине иерархии и родитель существует и корневой элемент

   Node *childNode = getNodeFromIndex(child); // указатель к типу node, вытаскиваем данные
   Node *parentNode = childNode->getParent();

   if (rootNode == parentNode) return result; // если равны, то корень

   result = createIndex(parentNode->childNumber(), 0, parentNode); // номер ряда, 0 -- столбец, указатель на данные
   return result;
}

int Model::rowCount(const QModelIndex &parent) const
{
    //if (!parent.isValid()) return 0;

    Node *parentNode = getNodeFromIndex(parent);
    if (parentNode)
        return parentNode->childrenCount();

    return 0;
}

int Model::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent); // игнорировать параметр
    return 1;
}

QVariant Model::data(const QModelIndex &index, int role) const // для опр индекса получение данных для каждой роли
{
    if (!index.isValid()) return QVariant();

    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole: {
        Node *indexNode = getNodeFromIndex(index);
        if (indexNode)
            return indexNode->getData();
    }
    default : break;
    }

    return QVariant();
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section>0) return QVariant(); // стобцов больше нуля быть не может
    if (orientation!=Qt::Horizontal) return QVariant();
    switch (role) {
        case Qt::DisplayRole: return "Наименование";
    default : break;
    }

    return QVariant();
}



Node *Model::getNodeFromIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        Node *node = static_cast<Node*>(index.internalPointer());
        if (node) return node;
    }
    return rootNode;
}


bool Model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) return false;

    Node *node = getNodeFromIndex(index);
    switch (role) {
    case Qt::EditRole: {
        if (node->setData(value.toString())) {
            QVector<int> roles;
            roles << Qt::DisplayRole;
            emit dataChanged(index, index, roles);
            return true;
        }
        break;
    }
    default: return false;
    }
    return false;
}

Qt::ItemFlags Model::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}


bool Model::removeRows(int row, int count, const QModelIndex &parent)
{
    Node *parentNode = getNodeFromIndex(parent);

    //сигнал модели о том, что сейчас будут удаляться элементы
    beginRemoveRows(parent, row, row+count-1);

    bool result = parentNode->removeNodes(row, count);

    //сигнал модели о том, что удаление элементов завершено
    endRemoveRows();
    return result;
}


bool Model::insertRows(int row, int count, const QModelIndex &parent)
{
    Node *parentNode = getNodeFromIndex(parent);

    beginInsertRows(parent, row, row+count-1);
    bool result = parentNode->insert(row, count);
    endInsertRows();

    return result;
}

void Model::moveUp(const QModelIndex &indexToMove)
{
    Node *node = getNodeFromIndex(indexToMove);
    Node *parent = node->getParent();

    int sourceChild = node->childNumber();
    int destChild = sourceChild;

    bool success = false;
    if (sourceChild == 0) {
        if (parent != rootNode) {
            destChild = parent->childNumber();
            beginMoveRows(indexToMove.parent(), sourceChild, sourceChild,
                          indexToMove.parent().parent(), destChild);

            Node *destParent = parent->getParent();

            if (parent->takeNode(node->childNumber())) {
                success = destParent->insertNode(destChild, node);
            }
            endMoveRows();
        }
    }
    else {
        destChild--;
        beginMoveRows(indexToMove.parent(), sourceChild, sourceChild, indexToMove.parent(), destChild);
        success = parent->moveNode(sourceChild, destChild);
        endMoveRows();
    }
}

void Model::moveDown(const QModelIndex &indexToMove)
{
    Node *node = getNodeFromIndex(indexToMove);
    Node *parent = node->getParent();

    int sourceChild = node->childNumber();
    int children = parent->childrenCount();

    int destChild = sourceChild;

    bool success = false;
    if (sourceChild < children-1) {
        destChild = sourceChild + 1;
        beginMoveRows(indexToMove.parent(), sourceChild, sourceChild,
                      indexToMove.parent(), destChild+1);

        success = parent->moveNode(sourceChild, destChild);
        endMoveRows();
    }
}
