#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QEvent>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QObject>

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "plane.h"
#include "enemyplane.h"
#include "constants.h"
#include "explosion.h"
#include "buffitem.h"
#include "playerhp.h"
#include "score.h"
#include "playerlife.h"
#include "background.h"
#include "timer.h"
#include "enemyboss.h"
#include "lists.h"


class Plane;
class EnemyPlane;
class Explosion;
class BuffItem;
class PlayerHP;
class Score;
class PlayerLife;
class Background;

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController(QGraphicsScene *scene, QObject *parent = 0);
    ~GameController();

    int getRandomNumber(int max);
    QGraphicsScene* getScene();
    void addEnemy(int a);
    void addEnemyGroup(int a);
    void removeEnemy(EnemyPlane *e);
    void removeBuff(BuffItem *b);
    void removeExplosion(Explosion *explosion);

public slots:
    void resume();
    void createEnemyPlane();
    void addEnemyPlaneGroup1();
    void moveEnemy();
    void moveBuff();
    void showExplosion();
    void playerDestroyed(Plane *plane);
    void refreshPlayerHP(int a);
    void createNewPlane();
    void getScore(int a);


private:
    QGraphicsScene *scene;
    Plane *plane;
    int enemyPlaneGroupCount;
    bool enemyPlaneGroupCreating;
    PlayerHP *playerHP;
    Score *score;
    PlayerLife *playerLife;
    Background *background;
    int difficulty;
    QLinkedList<EnemyPlane*> currentEnemyPlaneList;
    QLinkedList<BuffItem*> currentBuffList;
    QLinkedList<Explosion*> currentExplosionList;
};

#endif // GAMECONTROLLER_H
