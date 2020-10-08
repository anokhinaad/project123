#include "mainwindow.h"
#include <QtWidgets>
#include <QFileDialog>
#include <QAction>
#include <tree.h>
#include <model.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Работа с деревом");
    tree = new Tree(this);
    model = new Model();
    tree->setModel(model);

    openFileAction = new QAction ("Открыть файл", this);
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile())); // connect(openFileAction, &QAction::triggered, this, &MainWindow::openFile)
                                                                           // connect(openFileAction, &QAction::triggered, [=](){ openFile(); })

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
    QVBoxLayout *l = new QVBoxLayout(this); // упорядочивание по вертикали
    l->addWidget(tree);
    widget->setLayout(l); // установка компоновки

    setCentralWidget(widget);

    resize(500, 300);
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

        model->setModel(list);
    }
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

