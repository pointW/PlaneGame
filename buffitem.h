#ifndef BUFFITEM_H
#define BUFFITEM_H

#include "constants.h"
#include "flyitem.h"
#include "gamecontroller.h"
#include "plane.h"
#include "timer.h"

#include <QTimer>

class GameController;

class BuffItem : public FlyItem
{
    Q_OBJECT
public:
    BuffItem(BuffType t);
    ~BuffItem();

    void changeDirection();
    void move();
    BuffType getBuffType();
    void setDirectionAndSpeed();
    void resetBuff();

private:
    BuffType buffType;
    Direction direction;
    int directionChange;//方向改变次数
    int speed;
    int existCount;
};

#endif // BUFFITEM_H
