#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Tree;
class QAction;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void openFile();
    void saveFlie();
    void addElement();
    void delElement();
    void editElement();
    void upElement();
    void downElement();

private:
    Tree *tree;
    QAction *openFileAction; // открытие файла
    QAction *saveFlieAction; // сохранение в файл
    QAction *addElementAction; // добавить элемент
    QAction *delElementAction; // удалить элемент
    QAction *editElementAction; // редактировать элемент
    QAction *upElementAction; // переместить элемент вверх
    QAction *downElementAction; // переместить элемент вниз

    QMenu *fileMenu;
    QMenu *editMenu;
};
#endif // MAINWINDOW_H
