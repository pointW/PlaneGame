#include "playerlaser.h"

PlayerLaser::PlayerLaser(Plane *plane)
{
    setParent(plane);
    setData(GD_Type, GO_PlayerLaser);
    setPixmap(QPixmap(":/images/laser1"));
    setZValue(1);
}

PlayerLaser::~PlayerLaser()
{

}

void PlayerLaser::refreshPos(Direction d)
{
//    setPos(plane->getX(), plane->getY()-1000);
    switch(d){
    case Left:
        setX(getX()-10);
        break;
    case Right:
        setX(getX()+10);
        break;
    case Up:
        setY(getY()-10);
        break;
    case Down:
        setY(getY()+10);
        break;
    }
}
