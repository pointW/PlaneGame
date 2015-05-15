#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include "flyitem.h"
#include "constants.h"
#include "playerbullet.h"
#include "playermissile.h"
#include "playerlightingball.h"
#include "explosion.h"
#include "timer.h"

class GameController;

class EnemyPlane:public FlyItem
{
    Q_OBJECT
public:
    EnemyPlane(int a, QString name, GameController *game);
    ~EnemyPlane();
    void move();
    bool isHit();
    int getHP();
    void destroy();
    int getScore();

signals:
    void enemyDestroyed(EnemyPlane *enemy);

public slots:
    void posChange();
    void posChangeDown();
    void enemyCollisions();

private:
    QList<QGraphicsItem*> collisions;
    int HP;
    int speed;
    Direction direction;
    Direction nextDirection;
    int downTimes;//记录向下移动次数
    bool straightDown;//记录敌机是否属于简单向下
    int score;
};

#endif // ENEMYPLANE_H
