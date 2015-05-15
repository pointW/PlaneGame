#ifndef PLAYERLIGHTINGBALL_H
#define PLAYERLIGHTINGBALL_H

#include "flyitem.h"
#include "wingman.h"
#include "timer.h"

class Wingman;

class PlayerLightingBall:public FlyItem
{
    Q_OBJECT
public:
    PlayerLightingBall(int x, int y, Wingman *wingman);
    ~PlayerLightingBall();

    void aimTarget();

public slots:
    void changeImage();
    void changePos();

private:
    int imageNum;
    int target;
    int dx;
    int dy;
    double angle;
    int aimTimes;
    int speed;
};

#endif // PLAYERLIGHTINGBALL_H
