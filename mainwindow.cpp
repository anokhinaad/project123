#include "mainwindow.h"
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //tree = new Tree(this);

    openFileAction = new QAction ("Открыть файл", this);
    saveFlieAction = new QAction ("Сохранить файл", this);
    addElementAction = new QAction ("Добавить элемент", this);
    delElementAction = new QAction ("Удалить элемент", this);
    editElementAction = new QAction ("Редактировать элемент", this);
    upElementAction = new QAction ("Переместить элемент вверх", this);
    downElementAction = new QAction ("Переместить элемент вниз", this);

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

