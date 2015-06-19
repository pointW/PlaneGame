#ifndef BOSSHP_H
#define BOSSHP_H

#include <QGraphicsPixmapItem>

#include "constants.h"
#include "enemyboss.h"

class EnemyBoss;

class BossHP : public QObject
{
public:
    BossHP(EnemyBoss *boss, int maxHP);
    ~BossHP();

    void addToScene(QGraphicsScene *s);
    void setHP(double HP);
    void setVisiable(bool b);

private:
    QGraphicsPixmapItem *white;
    QGraphicsPixmapItem *red;
    QPixmap redPixmap;
    double max;

};

#endif // BOSSHP_H
