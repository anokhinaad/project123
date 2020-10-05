#include "model.h"

Model::Model()
{

}

void Model::clearModel()
{

}

void Model::setModel(const QStringList &lines)
{

}


QModelIndex Model::index(int row, int column, const QModelIndex &parent) const
{
}

QModelIndex Model::parent(const QModelIndex &child) const
{
}

int Model::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) return 0;
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
        case Qt::EditRole:
        //return static_cast<Node*>(index.internalPointer())->text();
        return QString("%1, %2").arg(index.row()).arg(index.column()); // проценты -- заменитель аргументов
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
