#include "enemyplane.h"

#include <QDebug>

EnemyPlane::EnemyPlane(int a, QString name, GameController *game)
{
    setParent(game);
    setObjectName(name);
    setData(GD_Type, GO_EnemyPlane);
    scene = game->getScene();
    connect(this, &EnemyPlane::enemyDestroyed, game, &GameController::enemyDestroyed);
    connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(enemyCollisions()));
    switch (a){
    case 1:
        setPixmap(QPixmap(":/images/enemyPlane1"));
        HP = 20;
        speed = 5;
        score = 20;
        direction = Down;
        straightDown = true;
        setX(getRandomNumber(LENGTH-80));
        setY(0);
        move();
        break;
    case 2:
        setPixmap(QPixmap(":/images/enemyPlane2"));
        HP = 40;
        speed = 2;
        score = 40;
        direction = Down;
        straightDown = true;
        setX(getRandomNumber(LENGTH-120));
        setY(0);
        move();
        break;
    case 3:
        setPixmap(QPixmap(":/images/enemyPlane3"));
        HP = 20;
        speed = 7;
        score = 20;
        direction = Right;
        straightDown = false;
        setX(0);
        setY(0);
        move();
        break;
    }
}

EnemyPlane::~EnemyPlane()
{

}

void EnemyPlane::move()
{
    if (straightDown){
        connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(posChangeDown()));
    }
    else {
        connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(posChange()));
    }

}

void EnemyPlane::posChangeDown()
{
    setY(getY()+speed);
    if (getY()>HEIGHT){
        deleteLater();
    }
}

void EnemyPlane::posChange()
{
    switch(direction){
    case Down:
        setY(getY()+speed);
        downTimes++;
        if (downTimes == 20){
            direction = nextDirection;
        }
        break;
    case Left:
        downTimes = 0;
        setX(getX()-speed);
        if (getX()<=0){
            direction = Down;
            nextDirection = Right;
        }
        break;
    case Right:
        downTimes = 0;
        setX(getX()+speed);
        if (getX()>=LENGTH-80){
            direction = Down;
            nextDirection = Left;
        }
        break;
    }
    if (getX()<0-boundingRect().width() || getX()>LENGTH ||
        getY()<0-boundingRect().height() || getY()>HEIGHT){
        deleteLater();
    }
}

bool EnemyPlane::isHit(){
    collisions = collidingItems();
    foreach (QGraphicsItem *collidingItem, collisions) {
        if (collidingItem->data(GD_Type) == GO_PlayerBullet) {
            PlayerBullet *b = dynamic_cast<PlayerBullet *>(collidingItem);
            b->deleteLater();
            HP-=10;
            return true;
        }
        else if (collidingItem->data(GD_Type) == GO_PlayerLaser){
            HP-=1;
            return true;
        }
        else if (collidingItem->data(GD_Type) == GO_PlayerMissile){
            HP-=20;
            PlayerMissile *m = dynamic_cast<PlayerMissile *>(collidingItem);
            m->deleteLater();
            return true;
        }
        else if (collidingItem->data(GD_Type) == GO_PlayerLightingBall){
            HP-=20;
            PlayerLightingBall *l = dynamic_cast<PlayerLightingBall *>(collidingItem);
            l->deleteLater();
            return true;
        }
    }
    return false;
}

int EnemyPlane::getHP()
{
    return HP;
}

void EnemyPlane::destroy()
{
    emit enemyDestroyed(this);
    deleteLater();
}

void EnemyPlane::enemyCollisions()
{
    if (isHit() && HP<=0){
        destroy();
    }
}

int EnemyPlane::getScore()
{
    return score;
}
