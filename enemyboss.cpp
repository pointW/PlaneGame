#include "enemyboss.h"

#include <QDebug>

EnemyBoss::EnemyBoss(int a, QString name, GameController *game)
{
    setParent(game);
    setObjectName(name);

    switch (a){
    case 1:
        setPixmap(QPixmap(":/images/boss1"));
        HP = 5000;
        maxHP = 5000;
        break;
    }
    setX((LENGTH-boundingRect().width())/2);
    setY(0);
    connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(posChangeDown()));
    bossHP = NULL;
    d = Left;
}

EnemyBoss::~EnemyBoss()
{

}

void EnemyBoss::posChangeDown()
{
    setY(y()+2);
    if (y()>=100){
        disconnect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(posChangeDown()));
        bossHP = new BossHP(this);
        connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(moveHorizontally()));
        connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(bossCollisions()));
        connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(moveBullet()));
        attack1();
    }
}

void EnemyBoss::moveHorizontally()
{
    switch(d){
    case Left:
        setX(x()-1);
        if (x()<=100){
            d = Right;
        }
        break;
    case Right:
        setX(x()+1);
        if (x()>=LENGTH-boundingRect().width()-100){
            d = Left;
        }
        break;
    default:
        break;
    }
}

void EnemyBoss::bossCollisions()
{
    collisions = collidingItems();
    foreach (QGraphicsItem *collidingItem, collisions) {
        if (collidingItem->data(GD_Type) == GO_PlayerBullet) {
            dynamic_cast<PlayerBullet *>(collidingItem)->setRemoveFlag(true);
            HP-=10;
        }
        else if (collidingItem->data(GD_Type) == GO_PlayerLaser){
            HP-=dynamic_cast<PlayerLaser *>(collidingItem)->damage();
        }
        else if (collidingItem->data(GD_Type) == GO_PlayerMissile){
            HP-=20;
            dynamic_cast<FlyItem *>(collidingItem)->setRemoveFlag(true);
        }
        else if (collidingItem->data(GD_Type) == GO_PlayerLightingBall){
            HP-=20;
            dynamic_cast<PlayerLightingBall *>(collidingItem)->deleteLater();
        }
    }
    bossHP->setHP(HP);
    qDebug()<<children().count();
}

void EnemyBoss::moveBullet()
{
    foreach (EnemyBullet *b, currentBossBullet){
        b->move();
        if (b->x()<0-b->boundingRect().width() || b->x()>LENGTH ||
            b->y()<0-b->boundingRect().height() || b->y()>HEIGHT){
            removeBullet(b);
        }
        else if (b->getRemoveFlag()){
            removeBullet(b);
        }
    }
}

void EnemyBoss::attack1()
{
    connect(Timer::getTimer5(), SIGNAL(timeout()), this, SLOT(attackWithBullet1()));
//    QTimer::singleShot(2000, this, SLOT(stopAttackWithBullet1()));
}

void EnemyBoss::attackWithBullet1()
{
    for (int i = 0; i<=350; i+=10){
        EnemyBullet *b = Lists::getEnemyBullet1();
        b->setPos(x()+boundingRect().width()/2, y()+boundingRect().height()/2);
        b->setAngle(i);
        b->setSpeed(5);
        b->setParent(this);
        QGraphicsItem::scene()->addItem(b);
        currentBossBullet.append(b);
    }
}

void EnemyBoss::stopAttackWithBullet1()
{
    disconnect(Timer::getTimer5(), SIGNAL(timeout()), this, SLOT(attackWithBullet1()));
}


void EnemyBoss::attack2()
{
    safeZone = 20;
    connect(Timer::getTimer5(), SIGNAL(timeout()), this, SLOT(attackWithBullet2()));
}

void EnemyBoss::attackWithBullet2()
{
//    for (int i = 0; i<=355; i+=10){
//        if (i>safeZone+30 || i<safeZone-30){
//            QGraphicsItem::scene()->addItem(new EnemyBullet(x()+boundingRect().width()/2, y()+boundingRect().height()/2, i, this, 3));
//        }
//    }
//    safeZone+=10;
//    if (safeZone>=170){
//        stopAttackWithBullet2();
//    }
}

void EnemyBoss::stopAttackWithBullet2()
{
    disconnect(Timer::getTimer5(), SIGNAL(timeout()), this, SLOT(attackWithBullet2()));
}

void EnemyBoss::removeBullet(EnemyBullet *b)
{
    currentBossBullet.removeOne(b);
    switch (b->getType()){
    case 1:
        Lists::recoverEnemyBullet1(b);
        break;
    }
}

