#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

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

    void About();



private:
    Tree *tree;
    Model *model;
    QAction *openFileAction; // открытие файла
    QAction *saveFileAction; // сохранение в файл
    QPushButton *addElementAction; // добавить элемент
    QPushButton *addChildElementAction; // доб дочерний элем
    QPushButton *delElementAction; // удалить элемент
    QPushButton *editElementAction; // редактировать элемент
    QPushButton *upElementAction; // переместить элемент вверх
    QPushButton *downElementAction; // переместить элемент вниз

    QAction *AboutAction; // о программе

    QMenu *fileMenu;
    QMenu *editMenu;


    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H
