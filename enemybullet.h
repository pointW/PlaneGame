#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "flyitem.h"
#include "timer.h"

class EnemyBullet:public FlyItem
{
    Q_OBJECT
public:
    EnemyBullet(int x, int y, int angle, QObject *parent);
    ~EnemyBullet();

public slots:
    void move();

private:
    int angle;
};

#endif // ENEMYBULLET_H
