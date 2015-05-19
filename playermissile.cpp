#include "playermissile.h"

#include <cmath>
#include <iostream>

using namespace std;

PlayerMissile::PlayerMissile()
{
    setZValue(-1);
    setData(GD_Type, GO_PlayerMissile);
    setPixmap(QPixmap(":/images/playerMissile"));
    aimTimes = 0;
    setTransformOriginPoint(20, 30);
}

PlayerMissile::~PlayerMissile()
{

}

void PlayerMissile::changeAngleAndPos()
{
    if (aimTimes>=3){
        changePos();
        return;
    }
    if (parent()->parent()->findChild<FlyItem *>("enemy"+QString::number(target, 10))==0)
    {
        aimTarget();
    }
    if (target!=-1){
        FlyItem *t = parent()->parent()->findChild<FlyItem *>("enemy"+QString::number(target, 10));
        dx = y() - (t->y()+t->boundingRect().height()/2);
        dy = x() - (t->x()+t->boundingRect().width()/2);
        double a = (180/3.14)*atan2(dy, dx);
        if (a<0){
            a+=360;
        }
        if (!(fabs(a-angle)<=20 || fabs(a-angle)>=350)){
            double x1, x2, y1, y2 = 0;
            x1 = cos(angle*(3.14/180));
            y1 = sin(angle*(3.14/180));
            x2 = dx;
            y2 = dy;
            if (x1*y2-x2*y1>0){
                angle+=5;
            }
            else if(x1*y2-x2*y1<0){
                angle-=5;
            }
            setRotation(-angle);
        }
    }
    changePos();
}

void PlayerMissile::changePos()
{
    setX(x()-10*sin(angle*(3.14/180)));
    setY(y()-10*cos(angle*(3.14/180)));
}

void PlayerMissile::aimTarget()
{
    for (int i = 0; i<=100; i++){
        target = i;
        if (parent()->parent()->findChild<FlyItem *>("enemy"+QString::number(target, 10))!=0){
            dx = y()-parent()->parent()->findChild<FlyItem *>("enemy"+QString::number(target, 10))->y();
            dy = x()-parent()->parent()->findChild<FlyItem *>("enemy"+QString::number(target, 10))->x();
            aimTimes++;
            break;
        }
        else {
            target = -1;
        }
    }
}

void PlayerMissile::setAngle(double a)
{
    angle = a;
}

void PlayerMissile::resetPlayerMissile()
{
    angle = 0;
    setRotation(angle);
    target = -1;
    aimTimes = 0;
    setParent(0);
    removeFlag = false;
    QGraphicsItem::scene()->removeItem(this);
}


