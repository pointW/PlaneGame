#include "lists.h"

QLinkedList<PlayerBullet*> Lists::playerBulletList = QLinkedList<PlayerBullet*>();
QLinkedList<PlayerMissile*> Lists::playerMissileList = QLinkedList<PlayerMissile*>();
QLinkedList<EnemyBullet*> Lists::enemyBullet1List = QLinkedList<EnemyBullet*>();
QLinkedList<EnemyPlane*> Lists::enemyPlane1List = QLinkedList<EnemyPlane*>();
QLinkedList<EnemyPlane*> Lists::enemyPlane2List = QLinkedList<EnemyPlane*>();
QLinkedList<EnemyPlane*> Lists::enemyPlane3List = QLinkedList<EnemyPlane*>();

Lists::Lists()
{

}

void Lists::createPlayerBulletList()
{
    for (int i = 0; i<=100; i++){
        playerBulletList.append(new PlayerBullet());
    }
}

PlayerBullet* Lists::getPlayerBullet()
{
    return playerBulletList.takeLast();
}

void Lists::recoverPlayerBullet(PlayerBullet *b)
{
    b->resetPlayerBullet();
    playerBulletList.append(b);
}

void Lists::createPlayerMissileList()
{
    for (int i = 0; i<=100; i++){
        playerMissileList.append(new PlayerMissile());
    }
}

PlayerMissile* Lists::getPlayerMissile()
{
    return playerMissileList.takeLast();
}

void Lists::recoverPlayerMissile(PlayerMissile *m)
{
    m->resetPlayerMissile();
    playerMissileList.append(m);
}

void Lists::createEnemyBullet1List()
{
    for (int i = 0; i<=1000; i++){
        enemyBullet1List.append(new EnemyBullet(1));
    }
}

EnemyBullet* Lists::getEnemyBullet1()
{
    return enemyBullet1List.takeLast();
}

void Lists::recoverEnemyBullet1(EnemyBullet *b)
{
    b->resetEnemyBullet();
    enemyBullet1List.append(b);
}

void Lists::createEnemyPlane1List()
{
    for (int i = 0; i<=20; i++){
        enemyPlane1List.append(new EnemyPlane(1));
    }
}

EnemyPlane* Lists::getEnemyPlane1()
{
    return enemyPlane1List.takeLast();
}

void Lists::recoverEnemyPlane1(EnemyPlane *p)
{
    p->resetEnemyPlane();
    enemyPlane1List.append(p);
}
