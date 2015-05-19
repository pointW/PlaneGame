#ifndef PLAYERMISSILE_H
#define PLAYERMISSILE_H

#include "constants.h"
#include "flyitem.h"
#include "gamecontroller.h"
#include "enemyplane.h"
#include "plane.h"
#include "timer.h"

class PlayerMissile:public FlyItem
{
    Q_OBJECT
public:
    PlayerMissile();
    ~PlayerMissile();

    void aimTarget();
    void changePos();
    void setAngle(double a);
    void resetPlayerMissile();
    void changeAngleAndPos();

private:
    int target;
    int dx;
    int dy;
    double angle;
    int aimTimes;
};

#endif // PLAYERMISSILE_H
