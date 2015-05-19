#ifndef LISTS_H
#define LISTS_H

#include "playerbullet.h"
#include "playermissile.h"

#include <QLinkedList>

class PlayerBullet;
class PlayerMissile;
class EnemyBullet;

class Lists
{
private:
    Lists();
    static QLinkedList<PlayerBullet*> playerBulletList;
    static QLinkedList<PlayerMissile*> playerMissileList;
    static QLinkedList<EnemyBullet*> enemyBullet1List;
    static QLinkedList<EnemyPlane*> enemyPlane1List;
    static QLinkedList<EnemyPlane*> enemyPlane2List;
    static QLinkedList<EnemyPlane*> enemyPlane3List;
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

    static void createEnemyPlane1List();
    static EnemyPlane* getEnemyPlane1();
    static void recoverEnemyPlane1(EnemyPlane *p);

    static void createEnemyPlane2List();
    static EnemyPlane* getEnemyPlane2();
    static void recoverEnemyPlane2(EnemyPlane *p);

    static void createEnemyPlane3List();
    static EnemyPlane* getEnemyPlane3();
    static void recoverEnemyPlane3(EnemyPlane *p);
};

#endif // LISTS_H
