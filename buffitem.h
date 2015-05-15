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
    BuffItem();
    BuffItem(BuffType BT, int x, int y, GameController *game);
    ~BuffItem();

    void changeDirection();
    void move();
    BuffType getBuffType();
//    int distenceToPlayer();
//    void flyToPlayer();

public slots:
    void changeBuffPos();

private:
    BuffType buffType;
    Direction direction;
    int directionChange;//方向改变次数
    QTimer *deletetimer;
    bool aimedPlayer;
    double angle;
    int speed;
};

#endif // BUFFITEM_H
