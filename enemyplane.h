#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include "flyitem.h"
#include "constants.h"
#include "playerbullet.h"
#include "playermissile.h"
#include "explosion.h"
#include "timer.h"

class GameController;

class EnemyPlane:public FlyItem
{
    Q_OBJECT
public:
    EnemyPlane();
    EnemyPlane(int t);
    ~EnemyPlane();
    void move();
    bool isHit();
    int getHP();
    int getScore();
    int getType();
    void resetEnemyPlane();
    void enemyCollisions();

private:
    QList<QGraphicsItem*> collisions;
    double HP;
    double maxHP;
    int speed;
    Direction direction;
    Direction nextDirection;
    int downTimes;//记录向下移动次数
    bool straightDown;//记录敌机是否属于简单向下
    int score;
    int type;
};

#endif // ENEMYPLANE_H
