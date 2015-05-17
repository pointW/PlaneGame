#include "enemybullet.h"

#include <cmath>
#include <iostream>

using namespace std;

EnemyBullet::EnemyBullet(int x, int y, int angle, QObject *parent)
{
    setData(GD_Type, GO_EnemyBullet);
    setPixmap(QPixmap(":/images/enemyBullet1"));
    setParent(parent);
    setZValue(-1);
    setX(x);
    setY(y);
    this->angle = angle;
    connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(move()));
}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::move()
{
    QGraphicsItem::setX(x()+5*cos(angle*(3.14/180)));
    QGraphicsItem::setY(y()+5*sin(angle*(3.14/180)));
    if (getX()<0-boundingRect().width() || getX()>LENGTH ||
        getY()<0-boundingRect().height() || getY()>HEIGHT){
        deleteLater();
    }
}
