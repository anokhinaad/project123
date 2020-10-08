#include "model.h"
#include <node.h>
#include <QMap>
#include <QMessageBox>

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
    foreach (const QString &s, lines) // указатель избавляет от копий
    {
        beginResetModel();

       QStringList list = s.split("#");
       const int listSize = list.size();
       if (listSize<=1) {
           QMessageBox::warning(0, "Ошибка в структуре данных", QString ("Строка %1 имеет неподходящую структуру. \n" "Она будет пропущена").arg(s));
           continue;
       }
        if (listSize==2){
              QMessageBox::warning(0, "Ошибка в структуре данных", QString ("Строка %1 имеет неподходящую структуру. \n" "Будет предпринята обработка строки").arg(s));

              // 3   #   1.1 Материал 1     1
              QStringList auxList = list.at(1).split(" ", QString::SkipEmptyParts);
              // получили 1.1|Материал|1|1
              if (auxList.size()>1) {
                  QString potentialParentString=auxList.last();

                  bool ok;
                  int potentialParentNumber=potentialParentString.toInt(&ok);
                  if (ok) {
                      list.append(potentialParentString);
                  }
                  else {
                      QMessageBox::warning(0, "Ошибка в структуре данных","Не удалось обработать строку");
                      continue;
                  }
              }
        }
        // обработка правильной строки
        QMap<int, Node*> nodesMap;

        int nodeIndex = list.first().simplified().toInt();
        QString data = list.at(1).trimmed();
        int parentIndex = list.at(2).simplified().toInt();

        // 1. Если pareniIndex=0, записываем в корень
        if (parentIndex==0){
             Node *currentNode = rootNode->insertNode(rootNode->childrenCount());
             currentNode->setData(data);
             nodesMap.insert(nodeIndex, currentNode);
        }
       else {
            Node *parentNode=nodesMap.value(parentIndex, 0);
            if (!parentNode) {
                QMessageBox::warning(0, "Ошибка в структуре данных","Не удалось обработать строку");
                continue;
            }
            Node *currentNode = parentNode->insertNode(parentNode->childrenCount());
            currentNode->setData(data);
            nodesMap.insert(nodeIndex, currentNode);
        }
    }

    endResetModel();
}

Node *Model::getNodeFromIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        Node *node = static_cast<Node*>(index.internalPointer());
        if (node) return node;
    }
    return rootNode;
}


QModelIndex Model::index(int row, int column, const QModelIndex &parent) const
{
  if (parent.isValid() && parent.column() != 0) return QModelIndex(); // только в 1 столбце существует
    Node *parentNode = getNodeFromIndex(parent); // static_cast<Node*>(parent.internalPointer());
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

   if (childNode==parentNode) return result; // если равны, то корень

   result = createIndex(parentNode->childNumber(), 0, parentNode); // номер ряда, 0 -- столбец, указатель на данные
}

int Model::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) return 0;
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
      //  return getNodeFromIndex(index)->getData();
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
