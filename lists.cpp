#include "lists.h"

QLinkedList<PlayerBullet*> Lists::playerBulletList = QLinkedList<PlayerBullet*>();
QLinkedList<PlayerMissile*> Lists::playerMissileList = QLinkedList<PlayerMissile*>();
QLinkedList<EnemyBullet*> Lists::enemyBullet1List = QLinkedList<EnemyBullet*>();
QLinkedList<EnemyPlane*> Lists::enemyPlane1List = QLinkedList<EnemyPlane*>();
QLinkedList<EnemyPlane*> Lists::enemyPlane2List = QLinkedList<EnemyPlane*>();
QLinkedList<EnemyPlane*> Lists::enemyPlane3List = QLinkedList<EnemyPlane*>();
QLinkedList<BuffItem*> Lists::buffList = QLinkedList<BuffItem*>();
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

void Lists::createEnemyPlaneList()
{
    for (int i = 0; i<=20; i++){
        enemyPlane1List.append(new EnemyPlane(1));
    }
    for (int i = 0; i<=20; i++){
        enemyPlane2List.append(new EnemyPlane(2));
    }
    for (int i = 0; i<=50; i++){
        enemyPlane3List.append(new EnemyPlane(3));
    }
}

EnemyPlane* Lists::getEnemyPlane(int t)
{
    switch (t){
    case 1:
        return enemyPlane1List.takeLast();
    case 2:
        return enemyPlane2List.takeLast();
    case 3:
        return enemyPlane3List.takeLast();
    }
    return NULL;
}

void Lists::recoverEnemyPlane(EnemyPlane *e)
{
    e->resetEnemyPlane();
    switch (e->getType()){
    case 1:
        enemyPlane1List.append(e);
        return;
    case 2:
        enemyPlane2List.append(e);
        return;
    case 3:
        enemyPlane3List.append(e);
        return;
    }
    return;
}

void Lists::createBuffList()
{
    for (int i = 0; i<20; i++){
        buffList.append(new BuffItem(TurnToBullet));
    }
    for (int i = 0; i<20; i++){
        buffList.append(new BuffItem(TurnToLaser));
    }
    for (int i = 0; i<20; i++){
        buffList.append(new BuffItem(LevelUp));
    }
    for (int i = 0; i<20; i++){
        buffList.append(new BuffItem(AddMissile));
    }
    for (int i = 0; i<100; i++){
        buffList.append(new BuffItem(Diamond));
    }
}

BuffItem* Lists::getBuff(BuffType t)
{
    foreach (BuffItem* buff, buffList){
        if (buff->getBuffType() == t){
            buffList.removeOne(buff);
            buff->setDirectionAndSpeed();
            return buff;
        }
    }
    return NULL;
}

void Lists::recoverBuff(BuffItem *b)
{
    b->resetBuff();
    buffList.append(b);
}

