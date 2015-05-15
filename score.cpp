#include "score.h"

Score::Score(GameController *game)
{
    score = 0;
    setParent(game);
    setHtml("score:0");
    setFont(QFont("AnyStyle", 20));
    setDefaultTextColor(QColor(255, 0, 0));
    setPos(10, 10);
    setZValue(10);
    game->getScene()->addItem(this);
}

Score::~Score()
{

}

void Score::addScore(int a)
{
    score+=a;
    setHtml("score:"+QString::number(score, 10));
}
