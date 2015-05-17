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
            PlayerBullet *b = dynamic_cast<PlayerBullet *>(collidingItem);
            b->deleteLater();
            HP-=10;
        }
        else if (collidingItem->data(GD_Type) == GO_PlayerLaser){
            HP-=dynamic_cast<PlayerLaser *>(collidingItem)->damage();
        }
        else if (collidingItem->data(GD_Type) == GO_PlayerMissile){
            HP-=20;
            PlayerMissile *m = dynamic_cast<PlayerMissile *>(collidingItem);
            m->deleteLater();
        }
        else if (collidingItem->data(GD_Type) == GO_PlayerLightingBall){
            HP-=20;
            PlayerLightingBall *l = dynamic_cast<PlayerLightingBall *>(collidingItem);
            l->deleteLater();
        }
    }
    bossHP->setHP(HP);
    qDebug()<<children().count();
}

void EnemyBoss::attack1()
{
    connect(Timer::getTimer5(), SIGNAL(timeout()), this, SLOT(attackWithBullet1()));
//    QTimer::singleShot(1000, this, SLOT(stopAttackWithBullet1()));
}

void EnemyBoss::attackWithBullet1()
{
    QGraphicsItem::scene()->addItem(new EnemyBullet(x()+boundingRect().width()/2, y()+boundingRect().height()/2, 0, this));
    QGraphicsItem::scene()->addItem(new EnemyBullet(x()+boundingRect().width()/2, y()+boundingRect().height()/2, 10, this));
    QGraphicsItem::scene()->addItem(new EnemyBullet(x()+boundingRect().width()/2, y()+boundingRect().height()/2, 20, this));
    QGraphicsItem::scene()->addItem(new EnemyBullet(x()+boundingRect().width()/2, y()+boundingRect().height()/2, 30, this));
    QGraphicsItem::scene()->addItem(new EnemyBullet(x()+boundingRect().width()/2, y()+boundingRect().height()/2, 40, this));
    QGraphicsItem::scene()->addItem(new EnemyBullet(x()+boundingRect().width()/2, y()+boundingRect().height()/2, 50, this));
    QGraphicsItem::scene()->addItem(new EnemyBullet(x()+boundingRect().width()/2, y()+boundingRect().height()/2, 60, this));
    QGraphicsItem::scene()->addItem(new EnemyBullet(x()+boundingRect().width()/2, y()+boundingRect().height()/2, 70, this));
    QGraphicsItem::scene()->addItem(new EnemyBullet(x()+boundingRect().width()/2, y()+boundingRect().height()/2, 80, this));
    QGraphicsItem::scene()->addItem(new EnemyBullet(x()+boundingRect().width()/2, y()+boundingRect().height()/2, 90, this));
    QGraphicsItem::scene()->addItem(new EnemyBullet(x()+boundingRect().width()/2, y()+boundingRect().height()/2, 100, this));
    QGraphicsItem::scene()->addItem(new EnemyBullet(x()+boundingRect().width()/2, y()+boundingRect().height()/2, 110, this));
    QGraphicsItem::scene()->addItem(new EnemyBullet(x()+boundingRect().width()/2, y()+boundingRect().height()/2, 120, this));
    QGraphicsItem::scene()->addItem(new EnemyBullet(x()+boundingRect().width()/2, y()+boundingRect().height()/2, 130, this));
    QGraphicsItem::scene()->addItem(new EnemyBullet(x()+boundingRect().width()/2, y()+boundingRect().height()/2, 140, this));
    QGraphicsItem::scene()->addItem(new EnemyBullet(x()+boundingRect().width()/2, y()+boundingRect().height()/2, 150, this));
    QGraphicsItem::scene()->addItem(new EnemyBullet(x()+boundingRect().width()/2, y()+boundingRect().height()/2, 160, this));
    QGraphicsItem::scene()->addItem(new EnemyBullet(x()+boundingRect().width()/2, y()+boundingRect().height()/2, 170, this));
    QGraphicsItem::scene()->addItem(new EnemyBullet(x()+boundingRect().width()/2, y()+boundingRect().height()/2, 180, this));
}

void EnemyBoss::stopAttackWithBullet1()
{
    disconnect(Timer::getTimer10(), SIGNAL(timeout()), this, SLOT(attackWithBullet1()));
}
