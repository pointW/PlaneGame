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
    double maxHP;

public slots:
    void posChangeDown();
    void moveHorizontally();
    void bossCollisions();
    void attack1();
    void attackWithBullet1();
    void stopAttackWithBullet1();
    void attack2();
    void attackWithBullet2();
    void stopAttackWithBullet2();


private:
    double HP;
    BossHP *bossHP;
    QList<QGraphicsItem*> collisions;
    Direction d;
    int safeZone;
};

#endif // ENEMYBOSS_H
