#include "playerlightingball.h"

#include <cmath>
#include <iostream>

using namespace std;

PlayerLightingBall::PlayerLightingBall(int x, int y, Wingman *wingman)
{
    setParent(wingman);
    imageNum = 1;
    setData(GD_Type, GO_PlayerLightingBall);
    angle = 0;
    aimTimes = 0;
    speed = 15;
    setX(x);
    setY(y);
    aimTarget();
    setTransformOriginPoint(20, 30);
    connect(Timer::getTimer(), SIGNAL(timeout()),
            this, SLOT(changePos()));
    connect(Timer::getTimer10(), SIGNAL(timeout()), this, SLOT(changeImage()));
}

PlayerLightingBall::~PlayerLightingBall()
{

}

void PlayerLightingBall::changeImage()
{
    switch(imageNum){
    case 1:
        setPixmap(QPixmap(":/images/lightingball1"));
        imageNum++;
        break;
    case 2:
        setPixmap(QPixmap(":/images/lightingball2"));
        imageNum++;
        break;
    case 3:
        setPixmap(QPixmap(":/images/lightingball3"));
        imageNum++;
        break;
    case 4:
        setPixmap(QPixmap(":/images/lightingball4"));
        imageNum++;
        break;
    case 5:
        setPixmap(QPixmap(":/images/lightingball5"));
        imageNum = 1;
        break;
    }
}

void PlayerLightingBall::changePos()
{
    if (aimTimes>=3){
        setX(x()-speed*sin(angle*(3.14/180)));
        setY(y()-speed*cos(angle*(3.14/180)));
        if (x()<0-boundingRect().width() || x()>LENGTH ||
            y()<0-boundingRect().height() || y()>HEIGHT){
            deleteLater();
        }
        return;
    }
    else if (parent()->parent()->parent()->findChild<EnemyPlane *>("enemy"+QString::number(target, 10))==0)
    {
        aimTarget();
    }
    if (target!=-1){
        dx = y() - parent()->parent()->parent()->findChild<EnemyPlane *>("enemy"+QString::number(target, 10))->y();
        dy = x() - parent()->parent()->parent()->findChild<EnemyPlane *>("enemy"+QString::number(target, 10))->x();
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
        }
    }
    setX(x()-speed*sin(angle*(3.14/180)));
    setY(y()-speed*cos(angle*(3.14/180)));
    if (x()<0-boundingRect().width() || x()>LENGTH ||
        y()<0-boundingRect().height() || y()>HEIGHT){
        deleteLater();
    }
}

void PlayerLightingBall::aimTarget()
{
    for (int i = 0; i<=100; i++){
        target = i;
        if (parent()->parent()->parent()->findChild<EnemyPlane *>("enemy"+QString::number(target, 10))!=0){
            dx = y() - parent()->parent()->parent()->findChild<EnemyPlane *>("enemy"+QString::number(target, 10))->y();
            dy = x() - parent()->parent()->parent()->findChild<EnemyPlane *>("enemy"+QString::number(target, 10))->x();
            aimTimes++;
            break;
        }
        else {
            target = -1;
        }
    }
}
