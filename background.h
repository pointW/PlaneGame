#ifndef BACKGROUND_H
#define BACKGROUND_H

#define BX 600
#define BY 923

#include "flyitem.h"
#include "constants.h"
#include "gamecontroller.h"
#include "timer.h"

#include <QGraphicsPixmapItem>

class Background:public QObject
{
    Q_OBJECT
public:
    Background(GameController *game);
    ~Background();
    void setY1(int y);
    void setY2(int y);

public slots:
    void posChange();

private:
    QGraphicsPixmapItem *b1;
    QGraphicsPixmapItem *b2;
    int y1;
    int y2;
};

#endif // BACKGROUND_H
