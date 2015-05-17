#include "playerhp.h"

PlayerHP::PlayerHP(GameController *game)
{
    setParent(game);
    white = new QGraphicsPixmapItem();
    red = new QGraphicsPixmapItem();
    white->setPos(20, HEIGHT-40);
    red->setPos(20+2, HEIGHT-40+2);
    white->setZValue(10);
    red->setZValue(11);
    game->getScene()->addItem(white);
    game->getScene()->addItem(red);
    white->setPixmap(QPixmap(":/images/playerHP1"));
    redPixmap = new QPixmap(":/images/playerHP2");
    red->setPixmap(redPixmap->copy(0, 0, 100-4, 20-4));
}

PlayerHP::~PlayerHP()
{
    delete redPixmap;
}

void PlayerHP::setHP(int a)
{
    red->setPixmap(redPixmap->copy(0, 0, a-4, 20-4));
}

void PlayerHP::playerDied()
{
    red->setVisible(false);
}

void PlayerHP::reset()
{
    red->setVisible(true);
    red->setPixmap(redPixmap->copy(0, 0, 100-4, 20-4));
}
