#ifndef PLAYERLASER_H
#define PLAYERLASER_H

#include "flyitem.h"
#include "plane.h"

class Plane;

class PlayerLaser : public FlyItem
{
    Q_OBJECT
public:
    PlayerLaser(Plane *plane);
    ~PlayerLaser();

public slots:
    void refreshPos(Direction d);

};

#endif // PLAYERLASER_H
