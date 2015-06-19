#include "playerlaser.h"

//PlayerLaser

PlayerLaser::PlayerLaser(Plane *plane)
{
    setZValue(1);
    setParent(plane);
    setData(GD_Type, GO_PlayerLaser);
    laser = new LaserMain(plane);
    ball = new LaserBall(plane);
    level = 1;
    addToGroup(laser);
    addToGroup(ball);
    connect(plane, &Plane::playerMoved, this, &PlayerLaser::refreshPos);
    connect(plane, &Plane::levelUp, this, &PlayerLaser::levelUp);
}

PlayerLaser::~PlayerLaser()
{

}

void PlayerLaser::refreshPos(Direction d)
{
    switch(d){
    case Left:
        setX(x()-10);
        break;
    case Right:
        setX(x()+10);
        break;
    case Up:
        setY(y()-10);
        break;
    case Down:
        setY(y()+10);
        break;
    default:
        break;
    }
}

void PlayerLaser::levelUp(int l)
{
    level = l;
}

int PlayerLaser::damage()
{
    return level;
}

//LaserMain

LaserMain::LaserMain(Plane *plane):
    Laser(QPixmap(":/images/laser2"), 90, 150)
{
    y = 0;
    setParent(plane);
    setZValue(1);
    setPixmap(image.copy(0, y, width, HEIGHT));
    setX(plane->x()+(PLAYERWIDTH-LASERWIDTH)/2);
    setY(plane->y()-HEIGHT-LASERBALLWIDTH/2);
    connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(moveLaser()));
    connect(plane, &Plane::levelUp, this, &LaserMain::levelUp);
}

void LaserMain::levelUp(int l)
{
    switch (l){
    case 1:
    case 2:
        image = QPixmap(":/images/laser2");
        break;
    case 3:
        image = QPixmap(":/images/laser1");
        break;
    case 4:
        image = QPixmap(":/images/laser3");
        break;
    }
}

//LaserBall

LaserBall::LaserBall(Plane *plane)
{
    setParent(plane);
    setPixmap(QPixmap(":/images/laserBall2"));
    setZValue(2);
    setX(plane->x()+(PLAYERWIDTH-LASERBALLWIDTH)/2);
    setY(plane->y()-LASERBALLWIDTH);
    angle = 0;
    setTransformOriginPoint(LASERBALLWIDTH/2, LASERBALLWIDTH/2);
    connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(ballRotation()));
    connect(plane, &Plane::levelUp, this, &LaserBall::levelUp);
}

void LaserBall::ballRotation(){
    angle+=20;
    if (angle>=360){
        angle = 0;
    }
    setRotation(angle);
}

void LaserBall::levelUp(int l)
{
    switch (l){
    case 1:
    case 2:
        setPixmap(QPixmap(":/images/laserBall2"));
        break;
    case 3:
        setPixmap(QPixmap(":/images/laserBall1"));
        break;
    case 4:
        setPixmap(QPixmap(":/images/laserBall3"));
        break;
    }
}
