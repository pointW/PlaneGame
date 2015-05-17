#ifndef BOSSHP_H
#define BOSSHP_H

#include <QGraphicsPixmapItem>

#include "constants.h"
#include "enemyboss.h"

class EnemyBoss;

class BossHP : public QObject
{
public:
    BossHP(EnemyBoss *boss);
    ~BossHP();

    void setHP(int a);

private:
    QGraphicsPixmapItem *white;
    QGraphicsPixmapItem *red;
    QPixmap redPixmap;
    int max;

};

#endif // BOSSHP_H
