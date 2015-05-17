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
//                dx = y()-parent()->findChild<Plane *>("player")->y();
//                dy = x()-parent()->findChild<Plane *>("player")->x();
//                angle = (180/3.14)*atan2(dy, dx);
//            }
//        }
//        flyToPlayer();
//        return;
//    }
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
    changeDirection();
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
//    return sqrt(pow(parent()->findChild<Plane *>("player")->x()-x(),2)+
//                pow(parent()->findChild<Plane *>("player")->y()-y(),2));
//}

//void BuffItem::flyToPlayer()
//{
//    if (parent()->findChild<Plane *>("player")==0){
//        setX(x()-10*sin(angle*(3.14/180)));
//        setY(y()-10*cos(angle*(3.14/180)));
//        return;
//    }
//    double dx, dy, x1, x2, y1, y2 = 0;
//    dx = y()-parent()->findChild<Plane *>("player")->y();
//    dy = x()-parent()->findChild<Plane *>("player")->x();
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
//    setX(x()-20*sin(angle*(3.14/180)));
//    setY(y()-20*cos(angle*(3.14/180)));
//    if (x()<0-50 || x()>LENGTH+50 ||
//        y()<0-50 || y()>HEIGHT+50){
//        deleteLater();
//    }
//}

