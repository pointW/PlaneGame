#include "buffitem.h"

#include <cmath>
#include <iostream>

using namespace std;

BuffItem::BuffItem()
{

}

BuffItem::BuffItem(BuffType BT, int x, int y, GameController *game)
{
    setParent(game);
    setData(GD_Type, GO_BuffItem);
    buffType = BT;
    aimedPlayer = false;
    angle = 0;
    speed = getRandomNumber(3)+2;
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

    setX(x);
    setY(y);
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
//    switch(direction){
//    case UpLeft:
//        angle = 45;
//        break;
//    case UpRight:
//        angle = -45;
//        break;
//    case DownLeft:
//        angle = 135;
//        break;
//    case DownRight:
//        angle = -135;
//        break;
//    }

    deletetimer = new QTimer(this);
    deletetimer->start(10000);
    connect(deletetimer, SIGNAL(timeout()), this, SLOT(deleteLater()));
    move();
}

BuffItem::~BuffItem()
{

}

void BuffItem::changeBuffPos()
{
//    if (buffType == Diamond && (aimedPlayer || distenceToPlayer()<=300)){
//        if (!aimedPlayer){
//            aimedPlayer = true;
//            double dx,dy = 0;
//            if (parent()->findChild<Plane *>("player")!=0){
//                dx = getY()-parent()->findChild<Plane *>("player")->getY();
//                dy = getX()-parent()->findChild<Plane *>("player")->getX();
//                angle = (180/3.14)*atan2(dy, dx);
//            }
//        }
//        flyToPlayer();
//        return;
//    }
    switch(direction){
    case UpLeft:
        setX(getX()-speed);
        setY(getY()-speed);
        break;
    case UpRight:
        setX(getX()+speed);
        setY(getY()-speed);
        break;
    case DownLeft:
        setX(getX()-speed);
        setY(getY()+speed);
        break;
    case DownRight:
        setX(getX()+speed);
        setY(getY()+speed);
        break;
    default:
        break;
    }
    changeDirection();
}

void BuffItem::changeDirection()
{
    if (getX()<=0){
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
    if (getX()>=LENGTH-boundingRect().width()){
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
    if (getY()<=0){
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
    if (getY()>=HEIGHT-boundingRect().height()){
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
//    switch(direction){
//    case UpLeft:
//        angle = 45;
//        break;
//    case UpRight:
//        angle = -45;
//        break;
//    case DownLeft:
//        angle = 135;
//        break;
//    case DownRight:
//        angle = -135;
//        break;
//    }
}

void BuffItem::move()
{
    connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(changeBuffPos()));
}

BuffType BuffItem::getBuffType()
{
    return buffType;
}

//int BuffItem::distenceToPlayer()
//{
//    if(parent()->findChild<Plane *>("player")==0){
//        return 1000;
//    }
//    return sqrt(pow(parent()->findChild<Plane *>("player")->getX()-getX(),2)+
//                pow(parent()->findChild<Plane *>("player")->getY()-getY(),2));
//}

//void BuffItem::flyToPlayer()
//{
//    if (parent()->findChild<Plane *>("player")==0){
//        setX(getX()-10*sin(angle*(3.14/180)));
//        setY(getY()-10*cos(angle*(3.14/180)));
//        return;
//    }
//    double dx, dy, x1, x2, y1, y2 = 0;
//    dx = getY()-parent()->findChild<Plane *>("player")->getY();
//    dy = getX()-parent()->findChild<Plane *>("player")->getX();
//    double a = (180/3.14)*atan2(dy, dx);
//    if (a<0){
//        a+=360;
//    }
//    x1 = cos(angle*(3.14/180));
//    y1 = sin(angle*(3.14/180));
//    x2 = dx;
//    y2 = dy;
//    if (x1*y2-x2*y1>0){
//        angle+=5;
//    }
//    else if(x1*y2-x2*y1<0){
//        angle-=5;
//    }
//    setX(getX()-20*sin(angle*(3.14/180)));
//    setY(getY()-20*cos(angle*(3.14/180)));
//    if (getX()<0-50 || getX()>LENGTH+50 ||
//        getY()<0-50 || getY()>HEIGHT+50){
//        deleteLater();
//    }
//}

