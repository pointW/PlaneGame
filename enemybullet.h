#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "flyitem.h"
#include "timer.h"

class EnemyBullet:public FlyItem
{
    Q_OBJECT
public:
    EnemyBullet(int x, int y, int angle, QObject *parent, int s = 5);
    ~EnemyBullet();

public slots:
    void move();

private:
    int angle;
    int speed;
};

#endif // ENEMYBULLET_H
