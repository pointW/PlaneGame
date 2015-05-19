#include "playerbullet.h"

PlayerBullet::PlayerBullet()
{
    setData(GD_Type, GO_PlayerBullet);
    setPixmap(QPixmap(":/images/redBullet"));
    removeFlag = false;
}

PlayerBullet::~PlayerBullet()
{

}

void PlayerBullet::move()
{
    switch(direction){
    case 1:
        moveBy(-20*0.38, -20*0.92);
        break;
    case 5:
        moveBy(20*0.38, -20*0.92);
        break;
    case 2:
        moveBy(-20*0.19, -20*0.98);
        break;
    case 4:
        moveBy(20*0.19, -20*0.98);
        break;
    case 3:
        moveBy(0, -20);
        break;
    }
}

void PlayerBullet::setDirection(int d)
{
    direction = d;
}

void PlayerBullet::resetPlayerBullet()
{
    setParent(0);
    removeFlag = false;
    QGraphicsItem::scene()->removeItem(this);
    direction = 0;
}
