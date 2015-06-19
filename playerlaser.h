#ifndef PLAYERLASER_H
#define PLAYERLASER_H

#include "flyitem.h"
#include "plane.h"
#include "timer.h"
#include "laser.h"

class Plane;

class LaserMain:public Laser
{
    Q_OBJECT
public:
    LaserMain(Plane *plane);
public slots:
    void levelUp(int l);
};

class LaserBall:public FlyItem
{
    Q_OBJECT
public:
    LaserBall(Plane *plane);
public slots:
    void ballRotation();
    void levelUp(int l);
private:
    int angle;
};

class PlayerLaser : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    PlayerLaser(Plane *plane);
    ~PlayerLaser();
    int damage();

public slots:
    void refreshPos(Direction d);
    void levelUp(int l);
private:
    LaserMain *laser;
    LaserBall *ball;
    int level;
};


#endif // PLAYERLASER_H
