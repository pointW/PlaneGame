#include "enemyplane.h"

#include <QDebug>

EnemyPlane::EnemyPlane()
{

}

EnemyPlane::EnemyPlane(int t)
{
    removeFlag = false;
    type = t;
    switch (t){
    case 1:
        setPixmap(QPixmap(":/images/enemyPlane1"));
        HP = 20;
        maxHP = 20;
        speed = 5;
        score = 20;
        direction = Down;
        straightDown = true;
        setData(GD_Type, GO_EnemyPlane);
        break;
    case 2:
        setPixmap(QPixmap(":/images/enemyPlane2"));
        HP = 40;
        maxHP = 40;
        speed = 2;
        score = 40;
        direction = Down;
        straightDown = true;
        setData(GD_Type, GO_EnemyPlane);
        break;
    case 3:
        setPixmap(QPixmap(":/images/enemyPlane3"));
        HP = 20;
        maxHP = 20;
        speed = 7;
        score = 20;
        direction = Right;
        straightDown = false;
        setData(GD_Type, GO_EnemyPlane);
        break;
    }
}

EnemyPlane::~EnemyPlane()
{

}

void EnemyPlane::move()
{
    if (straightDown){
        setY(y()+speed);
    }
    else {
        switch(direction){
        case Down:
            setY(y()+speed);
            downTimes++;
            if (downTimes == 20){
                direction = nextDirection;
            }
            break;
        case Left:
            downTimes = 0;
            setX(x()-speed);
            if (x()<=0){
                direction = Down;
                nextDirection = Right;
            }
            break;
        case Right:
            downTimes = 0;
            setX(x()+speed);
            if (x()>=LENGTH-80){
                direction = Down;
                nextDirection = Left;
            }
            break;
        default:
            break;
        }
    }
}

bool EnemyPlane::isHit(){
    collisions = collidingItems();
    foreach (QGraphicsItem *collidingItem, collisions) {
        if (collidingItem->data(GD_Type) == GO_PlayerBullet) {
            dynamic_cast<PlayerBullet *>(collidingItem)->setRemoveFlag(true);
            HP-=10;
            return true;
        }
        else if (collidingItem->data(GD_Type) == GO_PlayerLaser){
            HP-=dynamic_cast<PlayerLaser *>(collidingItem)->damage();
            return true;
        }
        else if (collidingItem->data(GD_Type) == GO_PlayerMissile){
            dynamic_cast<FlyItem *>(collidingItem)->setRemoveFlag(true);
            HP-=20;
            return true;
        }
    }
    return false;
}

int EnemyPlane::getHP()
{
    return HP;
}

void EnemyPlane::enemyCollisions()
{
    if (isHit() && HP<=0){
        removeFlag = true;
    }
}

int EnemyPlane::getScore()
{
    return score;
}

int EnemyPlane::getType()
{
    return type;
}

void EnemyPlane::resetEnemyPlane()
{
    setParent(0);
    removeFlag = false;
    QGraphicsItem::scene()->removeItem(this);
    HP = maxHP;
    switch (type){
    case 3:
        direction = Right;
        break;
    }
}
