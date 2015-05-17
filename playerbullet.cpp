#include "playerbullet.h"

PlayerBullet::PlayerBullet(int x, int y)
{
    setData(GD_Type, GO_PlayerBullet);
    setPixmap(QPixmap(":/images/redBullet"));
    setX(x);
    setY(y);
    direction = 3;
    connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(move()));
}

PlayerBullet::PlayerBullet(int x, int y, int direction)
{
    setData(GD_Type, GO_PlayerBullet);
    setPixmap(QPixmap(":/images/redBullet"));
    setX(x);
    setY(y);
    this->direction = direction;
    connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(move()));
}

PlayerBullet::~PlayerBullet()
{

}

void PlayerBullet::move()
{
    switch(direction){
    case 1:
        setX(x() - (20*0.38));
        setY(y() - (20*0.92));
        break;
    case 5:
        setX(x() + (20*0.38));
        setY(y() - (20*0.92));
        break;
    case 2:
        setX(x() - (20*0.19));
        setY(y() - (20*0.98));
        break;
    case 4:
        setX(x() + (20*0.19));
        setY(y() - (20*0.98));
        break;
    case 3:
        setY(y() - 20);
    }
    if (x()<0-boundingRect().width() || x()>LENGTH ||
        y()<0-boundingRect().height() || y()>HEIGHT){
        deleteLater();
    }
}
