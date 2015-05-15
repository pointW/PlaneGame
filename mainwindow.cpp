#include "mainwindow.h"

#ifndef QT_NO_OPENGL
# include <QtOpenGL/QtOpenGL>
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this)),
      view(new QGraphicsView(scene, this)),
      game(new GameController(scene, this))
{
    resize(LENGTH, HEIGHT);

    scene->setSceneRect(0, 0, LENGTH, HEIGHT);


#ifndef QT_NO_OPENGL
    view->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
#endif

    setCentralWidget(view);
}



MainWindow::~MainWindow()
{

}
