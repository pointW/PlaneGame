#ifndef PLAYERLASER_H
#define PLAYERLASER_H

#include "flyitem.h"
#include "plane.h"
#include "timer.h"

class Plane;

class LaserMain:public FlyItem
{
    Q_OBJECT
public:
    LaserMain(Plane *plane);
public slots:
    void moveLaser();
private:
    QPixmap *image;
    int y;
};

class LaserBall:public FlyItem
{
    Q_OBJECT
public:
    LaserBall(Plane *plane);
public slots:
    void ballRotation();
private:
    int angle;
};

class PlayerLaser : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    PlayerLaser(Plane *plane);
    ~PlayerLaser();

public slots:
    void refreshPos(Direction d);
//    void moveLaser();

private:
    LaserMain *laser;
    LaserBall *ball;
};


#endif // PLAYERLASER_H
