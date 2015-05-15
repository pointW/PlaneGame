#include "flyitem.h"

FlyItem::FlyItem()
{

}

FlyItem::~FlyItem()
{

}

int FlyItem::getX()
{
    return posX;
}

int FlyItem::getY()
{
    return posY;
}

void FlyItem::setX(int x)
{
    posX = x;
    setPos(posX, posY);
}

void FlyItem::setY(int y)
{
    posY = y;
    setPos(posX, posY);
}

int FlyItem::getRandomNumber(int max)
{
     return rand()%(max+1);//随机产生一个0至max的随机数
}
