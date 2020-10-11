#include "mainwindow.h"
#include <QtWidgets>
#include <QFileDialog>
#include <QAction>
#include <tree.h>
#include <model.h>
#include <QMessageBox>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Работа с деревом");
    tree = new Tree(this);
    model = new Model();
    tree->setModel(model);

    AboutAction = new QAction ("О программе", this);
    connect(AboutAction, SIGNAL(triggered()), this, SLOT(About()));

    openFileAction = new QAction ("Открыть файл", this);
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));

    saveFileAction = new QAction ("Сохранить файл", this);
    connect(saveFileAction, SIGNAL(triggered()), this, SLOT(saveFile()));

    addElementAction = new QPushButton ("Добавить элемент", this);
    connect(addElementAction, SIGNAL(released()), this, SLOT(addElement()));

    addChildElementAction = new QPushButton ("Добавить дочерний элемент", this);
    connect(addChildElementAction, SIGNAL(released()), this, SLOT(addChildElement()));

    delElementAction = new QPushButton ("Удалить элемент", this);
    connect(delElementAction, SIGNAL(released()), this, SLOT(delElement()));

    editElementAction = new QPushButton ("Редактировать элемент", this);
    connect(editElementAction, SIGNAL(released()), this, SLOT(editElement()));

    upElementAction = new QPushButton ("Переместить элемент вверх", this);
    connect(upElementAction, SIGNAL(released()), this, SLOT(upElement()));

    downElementAction = new QPushButton ("Переместить элемент вниз", this);
    connect(downElementAction, SIGNAL(released()), this, SLOT(downElement()));

    connect(tree->selectionModel(), &QItemSelectionModel::currentChanged,
            [=](const QModelIndex &current, const QModelIndex &previous){
        tree->closePersistentEditor(previous);
    });

    fileMenu = this->menuBar()->addMenu("Файл");
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(saveFileAction);

    editMenu = menuBar()->addMenu("Справка");
    editMenu->addAction(AboutAction);
   // editMenu->addAction(addElementAction);
    //editMenu->addAction(addChildElementAction);
    //editMenu->addAction(delElementAction);
    //editMenu->addAction(editElementAction);
    //editMenu->addAction(upElementAction);
    //editMenu->addAction(downElementAction);

    QWidget *widget = new QWidget(this);
    QVBoxLayout *l = new QVBoxLayout(this); // упорядочивание по вертикали
    l->addWidget(tree);

    l->addWidget(addElementAction);
    l->addWidget(addChildElementAction);
    l->addWidget(delElementAction);
    l->addWidget(editElementAction);
    l->addWidget(upElementAction);
    l->addWidget(downElementAction);

    widget->setLayout(l); // установка компоновки

    setCentralWidget(widget);

    resize(700, 500);
    show();
}

MainWindow::~MainWindow()
{

}

void MainWindow::openFile()
{
    QFileDialog dialog;
    QString fileName = dialog.getOpenFileName(this, "Выберите файл", QString(), "Текстовые файлы (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);

    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString content = file.readAll();
        QStringList list = content.split("\n");

        model->clearModel();
        model->setModel(list);
        setWindowTitle(QString("Работа с деревом - %1").arg(QFileInfo(fileName).fileName()));
    }
}

void MainWindow::saveFile()
{
    QFileDialog dialog;
    QString fileName = dialog.getSaveFileName(this, "Выберите файл", QString(), "Текстовые файлы (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);

    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QStringList list = model->getData();

        if (list.isEmpty()) {
            QMessageBox::critical(this, "Сохранение файла", "Не удалось получить данные");
            return;
        }

        file.write(list.join("\n").toUtf8());

        QMessageBox::information(this, "Сохранение файла", "Файл успешно сохранен");
    }
    else {
        QMessageBox::critical(this, "Сохранение файла", "Не удалось открыть файл");
    }
}

void MainWindow::addElement()
{
    QModelIndex index = tree->selectionModel()->currentIndex();

    if (index.isValid()) {
        if (!model->insertRow(index.row()+1, index.parent()))
            return;

        QModelIndex insertedRow = model->index(index.row()+1, 0, index.parent());
        model->setData(insertedRow, "[]", Qt::EditRole);

        tree->selectionModel()->setCurrentIndex(insertedRow, QItemSelectionModel::ClearAndSelect);
        tree->openPersistentEditor(insertedRow);
    }
}

void MainWindow::addChildElement()
{
    QModelIndex index = tree->selectionModel()->currentIndex();

    if (index.isValid()) {
        const int childrenCount = model->rowCount(index);
        if (!model->insertRow(childrenCount, index))
            return;

        //теперь childrenCount указывает на последний дочер элемент
        QModelIndex insertedChild = model->index(childrenCount, 0, index);
        model->setData(insertedChild, "[]", Qt::EditRole);

        tree->selectionModel()->setCurrentIndex(insertedChild, QItemSelectionModel::ClearAndSelect);
        tree->openPersistentEditor(insertedChild);
    }
}

void MainWindow::delElement()
{
    QModelIndex indexToDel = tree->selectionModel()->currentIndex();

    if (indexToDel.isValid()) {
        model->removeRow(indexToDel.row(), indexToDel.parent());
    }
}

void MainWindow::editElement()
{
    QModelIndex indexToEdit = tree->selectionModel()->currentIndex();

    if (indexToEdit.isValid()) {
        tree->openPersistentEditor(indexToEdit);
    }
}

void MainWindow::upElement()
{
    QModelIndex indexToMove = tree->selectionModel()->currentIndex();

    if (indexToMove.isValid()) {
        model->moveUp(indexToMove);
    }
}

void MainWindow::downElement()
{
    QModelIndex indexToMove = tree->selectionModel()->currentIndex();

    if (indexToMove.isValid()) {
        model->moveDown(indexToMove);
    }
}

void MainWindow::About()
{
    QMessageBox::information(this, "О программе", "В ходе выполнения тествого задания была реализована данная программа");

}



void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QModelIndex indexToEdit = tree->selectionModel()->currentIndex();
    if (event->key() == Qt::Key_Return && indexToEdit.isValid()) {
        tree->closePersistentEditor(indexToEdit);
    }
}
