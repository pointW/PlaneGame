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

public slots:
    void resume();
    void createEnemyPlane();
    void createEnemyPlaneGroup1();
    void enemyDestroyed(EnemyPlane *enemy);
    void playerDestroyed(Plane *plane);
    void refreshPlayerHP(int a);
    void createNewPlane();
    void getScore(int a);

protected:
//    bool eventFilter(QObject *object, QEvent *event);

private:
//    void handleKeyPressed(QKeyEvent *event);
//    void handleKeyRelease(QKeyEvent *event);

    QGraphicsScene *scene;
    Plane *plane;
    int enemyPlaneGroupCount;
    bool enemyPlaneGroupCreating;
    PlayerHP *playerHP;
    Score *score;
    PlayerLife *playerLife;
    Background *background;
    int difficulty;


};

#endif // GAMECONTROLLER_H
