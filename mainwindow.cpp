#include "mainwindow.h"
#include <QtWidgets>
#include <QAction>
#include <tree.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Работа с деревом");
    tree = new Tree(this);

    openFileAction = new QAction ("Открыть файл", this);
    saveFlieAction = new QAction ("Сохранить файл", this);
    addElementAction = new QAction ("Добавить элемент", this);
    delElementAction = new QAction ("Удалить элемент", this);
    editElementAction = new QAction ("Редактировать элемент", this);
    upElementAction = new QAction ("Переместить элемент вверх", this);
    downElementAction = new QAction ("Переместить элемент вниз", this);

    fileMenu = this->menuBar()->addMenu("Файл");
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(saveFlieAction);

    editMenu = menuBar()->addMenu("Правка");
    editMenu->addAction(addElementAction);
    editMenu->addAction(delElementAction);
    editMenu->addAction(editElementAction);
    editMenu->addAction(upElementAction);
    editMenu->addAction(downElementAction);

    QWidget *widget = new QWidget(this);
    QVBoxLayout *l = new QVBoxLayout(this);
    l->addWidget(tree);
    widget->setLayout(l);

    setCentralWidget(widget);

    resize(500, 300);
    show();
}

MainWindow::~MainWindow()
{

}

void MainWindow::openFile()
{

}

void MainWindow::saveFlie()
{

}

void MainWindow::addElement()
{

}

void MainWindow::delElement()
{

}

void MainWindow::editElement()
{

}

void MainWindow::upElement()
{

}

void MainWindow::downElement()
{

}

