#include "wingman.h"

Wingman::Wingman(int x, int y, int a, QString name, Plane *plane)
{
    setObjectName(name);
    setParent(plane);
    setX(x);
    setY(y);
    switch (a){
    case 1:
        setPixmap(QPixmap(":/images/wingmanL"));
        break;
    case 2:
        setPixmap(QPixmap(":/images/wingmanR"));
        break;
    }
    connect(plane, &Plane::playerMoved, this, &Wingman::refreshPos);
    connect(Timer::getTimer1(), SIGNAL(timeout()), this, SLOT(shootLightingBall()));
}

Wingman::~Wingman()
{

}

void Wingman::refreshPos(Direction d)
{
    switch(d){
    case Left:
        setX(getX()-10);
        break;
    case Right:
        setX(getX()+10);
        break;
    case Up:
        setY(getY()-10);
        break;
    case Down:
        setY(getY()+10);
        break;
    default:
        break;
    }
}

void Wingman::shootLightingBall()
{
    QGraphicsItem::scene()->addItem(new PlayerLightingBall(getX()+(boundingRect().width()-LIGHTINGBALLWIDTH)/2, getY()+60, this));
}
