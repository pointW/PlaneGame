#ifndef ENEMYBOSS_H
#define ENEMYBOSS_H

#include "flyitem.h"
#include "gamecontroller.h"
#include "timer.h"
#include "enemybullet.h"
#include "bosshp.h"

#include <QTimer>

class BossHP;

class EnemyBoss:public FlyItem
{
    Q_OBJECT
public:
    EnemyBoss(int a, QString name, GameController *game);
    ~EnemyBoss();
    int maxHP;

public slots:
    void posChangeDown();
    void bossCollisions();
    void attack1();
    void attackWithBullet1();
    void stopAttackWithBullet1();

private:
    int HP;
    BossHP *bossHP;
    QList<QGraphicsItem*> collisions;
};

#endif // ENEMYBOSS_H
