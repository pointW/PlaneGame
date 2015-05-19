#include "enemybullet.h"

#include <QGraphicsScene>

#include <cmath>
#include <iostream>

using namespace std;

EnemyBullet::EnemyBullet()
{

}

EnemyBullet::EnemyBullet(int t)
{
    switch (t){
    case 1:
        setPixmap(QPixmap(":/images/enemyBullet1"));
        setData(GD_Type, GO_EnemyBullet);
        setZValue(-1);
        removeFlag = false;
        type = 1;
    }
}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::move()
{
    QGraphicsItem::setX(x()+speed*cos(angle*(3.14/180)));
    QGraphicsItem::setY(y()+speed*sin(angle*(3.14/180)));
}

void EnemyBullet::resetEnemyBullet()
{
    setParent(0);
    removeFlag = false;
    QGraphicsItem::scene()->removeItem(this);
}

void EnemyBullet::setAngle(int a)
{
    angle = a;
}

void EnemyBullet::setSpeed(int s)
{
    speed = s;
}

int EnemyBullet::getType()
{
    return type;
}
