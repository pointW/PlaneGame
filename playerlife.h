#ifndef PLAYERLIFE_H
#define PLAYERLIFE_H

#include <QObject>
#include <QGraphicsPixmapItem>

#include "gamecontroller.h"

class PlayerLife:public QObject
{
    Q_OBJECT
public:
    PlayerLife(GameController *game);
    ~PlayerLife();
    void addLife();
    void decreaseLife();
    int getLife();

private:
    QGraphicsPixmapItem *life1;
    QGraphicsPixmapItem *life2;
    QGraphicsPixmapItem *life3;
    int life;
};

#endif // PLAYERLIFE_H
