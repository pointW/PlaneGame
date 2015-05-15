#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "plane.h"
#include "gamecontroller.h"
#include "constants.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QGraphicsPixmapItem>

class GameController;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;

    GameController *game;
};

#endif // MAINWINDOW_H
