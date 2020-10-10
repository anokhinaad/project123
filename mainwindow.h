#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Tree;
class QAction;
class Model;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void openFile();
    void saveFile();
    void addElement();
    void addChildElement();
    void delElement();
    void editElement();
    void upElement();
    void downElement();

private:
    Tree *tree;
    Model *model;
    QAction *openFileAction; // открытие файла
    QAction *saveFileAction; // сохранение в файл
    QAction *addElementAction; // добавить элемент
    QAction *addChildElementAction; // доб дочерний элем
    QAction *delElementAction; // удалить элемент
    QAction *editElementAction; // редактировать элемент
    QAction *upElementAction; // переместить элемент вверх
    QAction *downElementAction; // переместить элемент вниз

    QMenu *fileMenu;
    QMenu *editMenu;


    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H
