#ifndef ENEMYBOSS_H
#define ENEMYBOSS_H

#include "flyitem.h"
#include "gamecontroller.h"
#include "timer.h"
#include "enemybullet.h"
#include "bosshp.h"
#include "lists.h"

#include <QTimer>
#include <QLinkedList>

class BossHP;
class EnemyBullet;

class EnemyBoss:public FlyItem
{
    Q_OBJECT
public:
    EnemyBoss(int a);
    EnemyBoss(int a, QString name, GameController *game);
    ~EnemyBoss();
    void removeBullet(EnemyBullet *b);
    int getType();
    void resetBoss();
    void start();

public slots:
    void posChangeDown();
    void moveHorizontally();
    void bossCollisions();
    void attack1();
    void attack2();
    void attackWithBullet1();
    void stopAttackWithBullet1();
    void attackWithBullet2();
    void stopAttackWithBullet2();
    void moveBullet();

private:
    double HP;
    double maxHP;
    BossHP *bossHP;
    QList<QGraphicsItem*> collisions;
    Direction d;
    int safeZone;
    QLinkedList<EnemyBullet*> currentBossBullet;
    int type;
};

#endif // ENEMYBOSS_H
