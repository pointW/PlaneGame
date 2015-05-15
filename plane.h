#ifndef PLANE_H
#define PLANE_H

#include "flyitem.h"
#include "playerbullet.h"
#include "playerlaser.h"
#include "playermissile.h"
#include "gamecontroller.h"
#include "wingman.h"
#include "timer.h"

class PlayerBullet;
class GameController;
class PlayerLaser;


class Plane : public FlyItem
{

    Q_OBJECT
//    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    Plane(GameController *game);
    ~Plane();

    int getBulletCount();  
    void playerAttack();
    void attackWithBullet();
    void attackWithLaser();
    void stopAttack();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void stopLeft();
    void stopRight();
    void stopUp();
    void stopDown();
    void attackWithMissile();
    void handleSlop();
    void transformToSuper();
    void transformToNormal();
    void setTransformationImages();

public slots:
    void posChangeLeft();
    void posChangeRight();
    void posChangeUp();
    void posChangeDown();
    void creatBullet();
    void playerCollisions();
    AttackType getAttackType();
    void shootMissile();
    void playerUnbeatable();
    void backToStraight();
    void changeImageToSuper();
    void changeImageToNormal();
    void superState();
//    void moveWingmanFront();
//    void moveWingmanSide();

signals:
    void refreshHP(int a);
    void playerDestroyed(Plane *plane);
    void getScore(int a);
    void playerMoved(Direction d);

private:
    void handleKeyPressed(QKeyEvent *event);
    void handleKeyRelease(QKeyEvent *event);
    bool eventFilter(QObject *object, QEvent *event);


    GameController *gameController;
    PlayerLaser *laser;
    bool LeftFlag;
    bool RightFlag;
    bool UpFlag;
    bool DownFlag;//判断按下方向键时飞机是否已经处于移动状态
    bool bulletFlag;
    bool missileFlag;
    bool laserFlag;//判断飞机是否处于使用某武器攻击状态，与attackFlag不同
    bool attackFlag;//判断飞机是否在攻击
    bool visiable;
    bool beatable;
    AttackType attackType;
    int attackLevel;
    QList<QGraphicsItem*> collisions;
    int missileLevel;
    int HP;
    int unbeatableTimes;
    int slopFlag;
    bool transformingFlag;
    bool superFlag;
    int transformImagesFlag;
    bool wingmanFlag;
    int wingmanMoveFlag;
};

#endif // PLANE_H