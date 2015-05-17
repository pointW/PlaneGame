#ifndef FLYITEM_H
#define FLYITEM_H

#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QObject>
#include <QPoint>

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "constants.h"

class FlyItem : public QObject, public QGraphicsPixmapItem
{

    Q_OBJECT
//    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    FlyItem();
    ~FlyItem();

    int getRandomNumber(int max);

protected:
    QGraphicsScene *scene;
};

#endif // FLYITEM_H
