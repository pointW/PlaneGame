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
    Explosion(int x, int y, GameController *game);
    ~Explosion();

public slots:
    void showExplosion();

signals:
    void explosionEnd();

private:
    QPixmap *explosion1;

    int xCount;
    int yCount;

    bool isDone;
};

#endif // EXPLOSION_H
