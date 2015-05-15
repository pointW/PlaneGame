#include "explosion.h"

Explosion::Explosion(int x, int y, GameController *game)
{
    setParent(game);
    explosion1 = new QPixmap(":/images/explosion1");
    xCount = 0;
    yCount = 0;
    setPos(x, y);
    connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(showExplosion()));
}


Explosion::~Explosion()
{
    delete explosion1;
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
        setVisible(false);
        deleteLater();
    }
}



