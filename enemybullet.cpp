#include "enemybullet.h"

#include <cmath>
#include <iostream>

using namespace std;

EnemyBullet::EnemyBullet(int x, int y, int angle, QObject *parent, int s)
{
    setData(GD_Type, GO_EnemyBullet);
    setPixmap(QPixmap(":/images/enemyBullet1"));
    setParent(parent);
    setZValue(-1);
    setX(x);
    setY(y);
    this->angle = angle;
    speed = s;
    connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(move()));
}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::move()
{
    QGraphicsItem::setX(x()+speed*cos(angle*(3.14/180)));
    QGraphicsItem::setY(y()+speed*sin(angle*(3.14/180)));
    if (x()<0-boundingRect().width() || x()>LENGTH ||
        y()<0-boundingRect().height() || y()>HEIGHT){
        deleteLater();
    }
}
