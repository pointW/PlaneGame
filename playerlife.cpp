#include "playerlife.h"

PlayerLife::PlayerLife(GameController *game)
{
    setParent(game);
    life1 = new QGraphicsPixmapItem(QPixmap(":/images/playerLife"));
    life2 = new QGraphicsPixmapItem(QPixmap(":/images/playerLife"));
    life3 = new QGraphicsPixmapItem(QPixmap(":/images/playerLife"));
    life = 3;
    life1->setPos(140, HEIGHT-40);
    life2->setPos(140+30, HEIGHT-40);
    life3->setPos(140+60, HEIGHT-40);
    game->getScene()->addItem(life1);
    game->getScene()->addItem(life2);
    game->getScene()->addItem(life3);
}

PlayerLife::~PlayerLife()
{

}

void PlayerLife::addLife()
{
    switch(life){
    case 3:
        break;
    case 2:
        life3->setVisible(true);
        life++;
        break;
    case 1:
        life2->setVisible(true);
        life++;
        break;
    case 0:
        break;
    }
}

void PlayerLife::decreaseLife()
{
    switch(life){
    case 3:
        life3->setVisible(false);
        life--;
        break;
    case 2:
        life2->setVisible(false);
        life--;
        break;
    case 1:
        life1->setVisible(false);
        life--;
        break;
    case 0:
        break;
    }
}

int PlayerLife::getLife()
{
    return life;
}





