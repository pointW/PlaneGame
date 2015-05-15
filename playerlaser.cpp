#include "playerlaser.h"

//PlayerLaser

PlayerLaser::PlayerLaser(Plane *plane)
{
    setZValue(1);
    setParent(plane);
    laser = new LaserMain(plane);
    ball = new LaserBall(plane);
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
        laser->setX(laser->getX()-10);
        ball->setX(ball->getX()-10);
        break;
    case Right:
        laser->setX(laser->getX()+10);
        ball->setX(ball->getX()+10);
        break;
    case Up:
        laser->setY(laser->getY()-10);
        ball->setY(ball->getY()-10);
        break;
    case Down:
        laser->setY(laser->getY()+10);
        ball->setY(ball->getY()+10);
        break;
    default:
        break;
    }
}

void PlayerLaser::levelUp(int l)
{
    level = l;
}

//LaserMain

LaserMain::LaserMain(Plane *plane)
{
    image = new QPixmap(":/images/laser2");
    y = 0;
    setParent(plane);
    setZValue(1);
    setData(GD_Type, GO_PlayerLaser);
    setPixmap(image->copy(0, y, 90, 800));
    setX(plane->getX()+(PLAYERWIDTH-LASERWIDTH)/2);
    setY(plane->getY()-800-LASERBALLWIDTH/2);
    connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(moveLaser()));
    connect(plane, &Plane::levelUp, this, &LaserMain::levelUp);
}

void LaserMain::moveLaser()
{
    y+=15;
    if (y >= 150){
        y = 0;
    }
    setPixmap(image->copy(0, y, 90, 800));
}

void LaserMain::levelUp(int l)
{
    delete image;
    switch (l){
    case 1:
    case 2:
        image = new QPixmap(":/images/laser2");
    case 3:
    case 4:
        image = new QPixmap(":/images/laser1");
    case 5:
        image = new QPixmap(":/images/laser3");
    }
}

//LaserBall

LaserBall::LaserBall(Plane *plane)
{
    setParent(plane);
    setData(GD_Type, GO_PlayerLaser);
    setPixmap(QPixmap(":/images/laserBall2"));
    setZValue(2);
    setX(plane->getX()+(PLAYERWIDTH-LASERBALLWIDTH)/2);
    setY(plane->getY()-LASERBALLWIDTH);
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
    case 3:
    case 4:
        setPixmap(QPixmap(":/images/laserBall1"));
    case 5:
        setPixmap(QPixmap(":/images/laserBall3"));
    }
}
