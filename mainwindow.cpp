#include "mainwindow.h"
#include <QtWidgets>
#include <QFileDialog>
#include <QAction>
#include <tree.h>
#include <model.h>
#include <QMessageBox>

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
    connect(saveFlieAction, SIGNAL(triggered()), this, SLOT(saveFlie()));

    addElementAction = new QAction ("Добавить элемент", this);
    connect(addElementAction, SIGNAL(triggered()), this, SLOT(addElement()));

    delElementAction = new QAction ("Удалить элемент", this);
    connect(delElementAction, SIGNAL(triggered()), this, SLOT(delElement()));

    editElementAction = new QAction ("Редактировать элемент", this);
    connect(editElementAction, SIGNAL(triggered()), this, SLOT(editElement()));

    upElementAction = new QAction ("Переместить элемент вверх", this);
    connect(upElementAction, SIGNAL(triggered()), this, SLOT(upElement()));

    downElementAction = new QAction ("Переместить элемент вниз", this);
    connect(downElementAction, SIGNAL(triggered()), this, SLOT(downElement()));

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

        model->clearModel();

        model->setModel(list);
    }
}

void MainWindow::saveFlie()
{
    QFileDialog dialog;
    QString fileName = dialog.getSaveFileName(this, "Выберите файл", QString(), "Текстовые файлы (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    QStringList list;
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QString content = file.readAll();

        QStringList list = model->getData();

        if (list.isEmpty()) {
            QMessageBox::critical(this, "Сохранение файла", "Не удалось получить данные");
            return;
        }

        file.write(list.join("\n").toUtf8());

        QMessageBox::information(this, "Сохранение файла", "Файл успешно сохранён");
    }
    else {
        QMessageBox::critical(this, "Сохранение файла", "Не удалось открыть файл");
    }
}

void MainWindow::addElement()
{

}

void MainWindow::delElement()
{

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

}

void MainWindow::downElement()
{

}

