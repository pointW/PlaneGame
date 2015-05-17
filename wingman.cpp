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
        setX(x()-10);
        break;
    case Right:
        setX(x()+10);
        break;
    case Up:
        setY(y()-10);
        break;
    case Down:
        setY(y()+10);
        break;
    default:
        break;
    }
}

void Wingman::shootLightingBall()
{
    QGraphicsItem::scene()->addItem(new PlayerLightingBall(x()+(boundingRect().width()-LIGHTINGBALLWIDTH)/2, y()+60, this));
}
