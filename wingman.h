#ifndef WINGMAN_H
#define WINGMAN_H

#include "flyitem.h"
#include "plane.h"
#include "playerlightingball.h"
#include "timer.h"

class Plane;

class Wingman:public FlyItem
{
    Q_OBJECT
public:
    Wingman(int x, int y, int a, QString name, Plane *plane);
    ~Wingman();

public slots:
    void refreshPos(Direction d);
    void shootLightingBall();
};

#endif // WINGMAN_H
