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
        setX(getX() - (20*0.38));
        setY(getY() - (20*0.92));
        break;
    case 5:
        setX(getX() + (20*0.38));
        setY(getY() - (20*0.92));
        break;
    case 2:
        setX(getX() - (20*0.19));
        setY(getY() - (20*0.98));
        break;
    case 4:
        setX(getX() + (20*0.19));
        setY(getY() - (20*0.98));
        break;
    case 3:
        setY(getY() - 20);
    }
    if (getX()<0-boundingRect().width() || getX()>LENGTH ||
        getY()<0-boundingRect().height() || getY()>HEIGHT){
        deleteLater();
    }
}
