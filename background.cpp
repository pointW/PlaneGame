#include "background.h"

Background::Background(GameController *game)
{
    setParent(game);
    b1 = new QGraphicsPixmapItem();
    b2 = new QGraphicsPixmapItem();
    game->getScene()->addItem(b1);
    game->getScene()->addItem(b2);
    b1->setPixmap(QPixmap(":/images/background2"));
    b2->setPixmap(QPixmap(":/images/background2"));
    b1->setZValue(-1);
    b2->setZValue(-1);
    setY1(-(BY-HEIGHT));
    setY2(-(2*BY-HEIGHT));
    connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(posChange()));

}

Background::~Background()
{

}

void Background::setY1(int y)
{
    y1 = y;
    b1->setPos(0, y1);
}

void Background::setY2(int y)
{
    y2 = y;
    b2->setPos(0, y2);
}

void Background::posChange()
{
    setY1(y1+1);
    setY2(y2+1);
    if (y1==HEIGHT){
        setY1(y2-BY);
    }
    if (y2==HEIGHT){
        setY2(y1-BY);
    }
}
