#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

#include "gamecontroller.h"
#include "constants.h"

class Score : public QGraphicsTextItem
{
    Q_OBJECT
public:
    Score(GameController *game);
    ~Score();
    void addScore(int a);

private:
    int score;
};

#endif // SCORE_H
