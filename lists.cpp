#include "lists.h"

QLinkedList<PlayerBullet*> Lists::playerBulletList = QLinkedList<PlayerBullet*>();
QLinkedList<PlayerMissile*> Lists::playerMissileList = QLinkedList<PlayerMissile*>();
QLinkedList<EnemyBullet*> Lists::enemyBullet1List = QLinkedList<EnemyBullet*>();
QLinkedList<EnemyPlane*> Lists::enemyPlaneList = QLinkedList<EnemyPlane*>();
QLinkedList<BuffItem*> Lists::buffList = QLinkedList<BuffItem*>();
QLinkedList<Explosion*> Lists::explosionList = QLinkedList<Explosion*>();
QLinkedList<EnemyBoss*> Lists::bossList = QLinkedList<EnemyBoss*>();
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
        enemyPlaneList.append(new EnemyPlane(1));
    }
    for (int i = 0; i<=20; i++){
        enemyPlaneList.append(new EnemyPlane(2));
    }
    for (int i = 0; i<=50; i++){
        enemyPlaneList.append(new EnemyPlane(3));
    }
}

EnemyPlane* Lists::getEnemyPlane(int t)
{
    foreach (EnemyPlane *e, enemyPlaneList){
        if (e->getType() == t){
            enemyPlaneList.removeOne(e);
            return e;
        }
    }
    return NULL;
}

void Lists::recoverEnemyPlane(EnemyPlane *e)
{
    e->resetEnemyPlane();
    enemyPlaneList.append(e);
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

void Lists::createExplosionList()
{
    for (int i = 0; i<=50; i++){
        explosionList.append(new Explosion(1));
    }
}

Explosion* Lists::getExplosion()
{
    return explosionList.takeLast();
}

void Lists::recoverExplosion(Explosion *e)
{
    e->resetExplosion();
    explosionList.append(e);
}

void Lists::createBossList()
{
    bossList.append(new EnemyBoss(1));
}

EnemyBoss* Lists::getBoss(int i)
{
    foreach (EnemyBoss *boss, bossList){
        if (boss->getType() == i){
            return boss;
        }
    }
    return NULL;
}

void Lists::recoverBoss(EnemyBoss *boss)
{
    boss->resetBoss();
    bossList.append(boss);
}
