#include "playerlaser.h"

PlayerLaser::PlayerLaser(Plane *plane)
{
//    ball = new LaserBall(this);
//    laser = new QPixmap(":/images/laser2");
//    y = 0;
//    setParent(plane);
//    setData(GD_Type, GO_PlayerLaser);
//    setPixmap(laser->copy(0, y, 90, 800));
//    setZValue(1);
//    connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(moveLaser()));
    setParent(plane);
    laser = new LaserMain(plane);
    ball = new LaserBall(plane);
    addToGroup(laser);
    addToGroup(ball);
    connect(plane, &Plane::playerMoved, this, &PlayerLaser::refreshPos);
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

//void PlayerLaser::moveLaser()
//{
//    y+=10;
//    if (y >= 150){
//        y = 0;
//    }
//    setPixmap(laser->copy(0, y, 90, 800));
//}

LaserMain::LaserMain(Plane *plane)
{
    image = new QPixmap(":/images/laser2");
    y = 0;
    setParent(plane);
    setData(GD_Type, GO_PlayerLaser);
    setPixmap(image->copy(0, y, 90, 800));
    setZValue(1);
    setX(plane->getX()+(PLAYERWIDTH-LASERWIDTH)/2);
    setY(plane->getY()-800-LASERBALLWIDTH/2);
    connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(moveLaser()));
}

void LaserMain::moveLaser()
{
    y+=15;
    if (y >= 150){
        y = 0;
    }
    setPixmap(image->copy(0, y, 90, 800));
}

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
}

void LaserBall::ballRotation(){
    angle+=15;
    if (angle>=360){
        angle = 0;
    }
    setRotation(angle);
}
