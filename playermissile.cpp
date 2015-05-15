#include "playermissile.h"

#include <cmath>
#include <iostream>

using namespace std;

PlayerMissile::PlayerMissile(int x, int y, QObject *parent)
{
    setParent(parent);
    setZValue(-1);
    setData(GD_Type, GO_PlayerMissile);
    setPixmap(QPixmap(":/images/playerMissile"));
    angle = 0;
    aimTimes = 0;
    setX(x);
    setY(y);
    aimTarget();
    setTransformOriginPoint(20, 30);
    connect(Timer::getTimer(), SIGNAL(timeout()),
            this, SLOT(changeAngleAndPos()));
}

PlayerMissile::PlayerMissile(int x, int y, int angle, QObject *parent)
{
    setParent(parent);
    setZValue(-1);
    setData(GD_Type, GO_PlayerMissile);
    setPixmap(QPixmap(":/images/playerMissile"));
    this->angle = angle;
    setRotation(-angle);
    aimTimes = 0;
    setX(x);
    setY(y);
    aimTarget();
    setTransformOriginPoint(20, 30);
    connect(Timer::getTimer(), SIGNAL(timeout()),
            this, SLOT(changeAngleAndPos()));
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
    if (parent()->parent()->findChild<EnemyPlane *>("enemy"+QString::number(target, 10))==0)
    {
        aimTarget();
    }
    if (target!=-1){
        dx = getY() - parent()->parent()->findChild<EnemyPlane *>("enemy"+QString::number(target, 10))->getY();
        dy = getX() - parent()->parent()->findChild<EnemyPlane *>("enemy"+QString::number(target, 10))->getX();
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
    if (getX()<0-boundingRect().width() || getX()>LENGTH ||
        getY()<0-boundingRect().height() || getY()>HEIGHT){
        deleteLater();
    }
}

void PlayerMissile::changePos()
{
    setX(getX()-10*sin(angle*(3.14/180)));
    setY(getY()-10*cos(angle*(3.14/180)));
}

void PlayerMissile::aimTarget()
{
    for (int i = 0; i<=100; i++){
        target = i;
        if (parent()->parent()->findChild<EnemyPlane *>("enemy"+QString::number(target, 10))!=0){
            dx = getY()-parent()->parent()->findChild<EnemyPlane *>("enemy"+QString::number(target, 10))->getY();
            dy = getX()-parent()->parent()->findChild<EnemyPlane *>("enemy"+QString::number(target, 10))->getX();
            aimTimes++;
            break;
        }
        else {
            target = -1;
        }
    }
}







