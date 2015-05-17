#ifndef PLAYERHP_H
#define PLAYERHP_H

#include <QGraphicsPixmapItem>

#include "gamecontroller.h"
#include "constants.h"

class PlayerHP : public QObject
{
    Q_OBJECT
public:
    PlayerHP(GameController *game);
    ~PlayerHP();

    void setHP(int a);
    void playerDied();
    void reset();

private:
    QGraphicsPixmapItem *white;
    QGraphicsPixmapItem *red;
    QPixmap *redPixmap;
};

#endif // PLAYERHP_H
