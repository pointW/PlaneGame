#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include "flyitem.h"
#include "timer.h"
#include "plane.h"

class Plane;

class PlayerBullet : public FlyItem
{

    Q_OBJECT
//    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    PlayerBullet();
    PlayerBullet(int x, int y, Plane *plane, int direction = 3);
    ~PlayerBullet();
    void setDirection(int d);
    void move();
    void resetPlayerBullet();

protected:
    int direction;//1-5，子弹方向，1为左上45°，5为右上45°
};

#endif // PLAYERBULLET_H
