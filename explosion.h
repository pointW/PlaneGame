#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QGraphicsPixmapItem>
#include <QObject>

#include "flyitem.h"
#include "gamecontroller.h"
#include "timer.h"

class GameController;

class Explosion : public FlyItem
{
    Q_OBJECT
public:
    Explosion(int t);
    ~Explosion();
    void resetExplosion();
    void showExplosion();

private:
    QPixmap *explosion1;
    int xCount;
    int yCount;
    int type;
};

#endif // EXPLOSION_H
