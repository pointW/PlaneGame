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

    void setRemoveFlag(bool f);
    bool getRemoveFlag();

    int getRandomNumber(int max);

protected:
    QGraphicsScene *scene;
    bool removeFlag;
};

#endif // FLYITEM_H
