#ifndef LISTS_H
#define LISTS_H

#include "playerbullet.h"
#include "playermissile.h"

#include <QLinkedList>

class PlayerBullet;
class PlayerMissile;
class EnemyBullet;
class EnemyPlane;
class BuffItem;
class Explosion;
class EnemyBoss;

class Lists
{
private:
    Lists();
    static QLinkedList<PlayerBullet*> playerBulletList;
    static QLinkedList<PlayerMissile*> playerMissileList;
    static QLinkedList<EnemyBullet*> enemyBullet1List;
    static QLinkedList<EnemyPlane*> enemyPlaneList;
    static QLinkedList<BuffItem*> buffList;
    static QLinkedList<Explosion*> explosionList;
    static QLinkedList<EnemyBoss*> bossList;
public:
    static void createPlayerBulletList();
    static PlayerBullet* getPlayerBullet();
    static void recoverPlayerBullet(PlayerBullet *b);

    static void createPlayerMissileList();
    static PlayerMissile* getPlayerMissile();
    static void recoverPlayerMissile(PlayerMissile *m);

    static void createEnemyBullet1List();
    static EnemyBullet* getEnemyBullet1();
    static void recoverEnemyBullet1(EnemyBullet *b);

    static void createEnemyPlaneList();
    static EnemyPlane* getEnemyPlane(int t);
    static void recoverEnemyPlane(EnemyPlane *e);

    static void createBuffList();
    static BuffItem* getBuff(BuffType t);
    static void recoverBuff(BuffItem *b);

    static void createExplosionList();
    static Explosion* getExplosion();
    static void recoverExplosion(Explosion *e);

    static void createBossList();
    static EnemyBoss* getBoss(int i);
    static void recoverBoss(EnemyBoss *boss);
};

#endif // LISTS_H
