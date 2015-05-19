#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "flyitem.h"
#include "timer.h"

class EnemyBoss;

class EnemyBullet:public FlyItem
{
    Q_OBJECT
public:
    EnemyBullet();
    EnemyBullet(int t);
    ~EnemyBullet();
    void move();
    void setAngle(int a);
    void setSpeed(int s);
    void resetEnemyBullet();
    int getType();

private:
    int angle;
    int speed;
    int type;
};

#endif // ENEMYBULLET_H
