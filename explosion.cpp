#include "explosion.h"

Explosion::Explosion(int t)
{
    switch (t){
    case 1:
        type = 1;
        explosion1 = new QPixmap(":/images/explosion1");
        break;
    }
    xCount = 0;
    yCount = 0;
    removeFlag = false;
}

Explosion::~Explosion()
{
    delete explosion1;
}

void Explosion::resetExplosion()
{
    setParent(0);
    removeFlag = false;
    QGraphicsItem::scene()->removeItem(this);
    xCount = 0;
    yCount = 0;
}

void Explosion::showExplosion()
{
    setPixmap(explosion1->copy(128*xCount, 128*yCount, 128, 128));
    xCount++;
    if (xCount == 10 && yCount == 0){
        xCount = 0;
        yCount = 1;
    }
    if (xCount == 10 && yCount == 1){
        removeFlag = true;
    }
}



