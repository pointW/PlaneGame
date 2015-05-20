#include "buffitem.h"

#include <cmath>
#include <iostream>

using namespace std;

BuffItem::BuffItem()
{

}

BuffItem::BuffItem(BuffType t)
{
    setData(GD_Type, GO_BuffItem);
    buffType = t;
    existCount = 0;
    switch(buffType){
    case TurnToLaser:
        setPixmap(QPixmap(":/images/turnToLaser"));
        break;
    case TurnToBullet:
        setPixmap(QPixmap(":/images/turnToBullet"));
        break;
    case LevelUp:
        setPixmap(QPixmap(":/images/levelUp"));
        break;
    case AddMissile:
        setPixmap(QPixmap(":/images/addMissile"));
        break;
    case Diamond:
        setPixmap(QPixmap(":/images/diamond"));
        break;
    }
}

BuffItem::~BuffItem()
{

}

void BuffItem::changeDirection()
{
    if (x()<=0){
        switch(direction){
        case UpLeft:
            direction = UpRight;
            break;
        case DownLeft:
            direction = DownRight;
            break;
        default:
            break;
        }
    }
    if (x()>=LENGTH-boundingRect().width()){
        switch(direction){
        case UpRight:
            direction = UpLeft;
            break;
        case DownRight:
            direction = DownLeft;
            break;
        default:
            break;
        }
    }
    if (y()<=0){
        switch(direction){
        case UpLeft:
            direction = DownLeft;
            break;
        case UpRight:
            direction = DownRight;
            break;
        default:
            break;
        }
    }
    if (y()>=HEIGHT-boundingRect().height()){
        switch(direction){
        case DownLeft:
            direction = UpLeft;
            break;
        case DownRight:
            direction = UpRight;
            break;
        default:
            break;
        }
    }
}

void BuffItem::move()
{
    switch(direction){
    case UpLeft:
        setX(x()-speed);
        setY(y()-speed);
        break;
    case UpRight:
        setX(x()+speed);
        setY(y()-speed);
        break;
    case DownLeft:
        setX(x()-speed);
        setY(y()+speed);
        break;
    case DownRight:
        setX(x()+speed);
        setY(y()+speed);
        break;
    default:
        break;
    }
    existCount++;
    if (existCount>=600){
        removeFlag = true;
    }
    changeDirection();
}

BuffType BuffItem::getBuffType()
{
    return buffType;
}

void BuffItem::setDirectionAndSpeed()
{
    switch(getRandomNumber(3)){
    case 0:
        direction = UpLeft;
        break;
    case 1:
        direction = UpRight;
        break;
    case 2:
        direction = DownLeft;
        break;
    case 3:
        direction = DownRight;
        break;
    }
    speed = getRandomNumber(3)+2;
}

void BuffItem::resetBuff()
{
    setParent(0);
    removeFlag = false;
    QGraphicsItem::scene()->removeItem(this);
    setDirectionAndSpeed();
    existCount = 0;
}
