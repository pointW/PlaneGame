#include "gamecontroller.h"
#include "mainwindow.h"

#include <QDebug>
#include <QPainter>

GameController::GameController(QGraphicsScene *s, QObject *parent) :
    QObject(parent),
    scene(s),
    plane(new Plane(this)),
    enemyPlaneGroupCount(0),
    enemyPlaneGroupCreating(false)
{
    Lists::createPlayerBulletList();
    Lists::createPlayerMissileList();
    Lists::createEnemyBullet1List();
    Lists::createEnemyPlaneList();
    srand((unsigned int)time(NULL));

    difficulty = 1;

    playerHP = new PlayerHP(this);
    score = new Score(this);
    playerLife = new PlayerLife(this);
    background = new Background(this);

    resume();
}

GameController::~GameController()
{

}

void GameController::resume()
{
    connect(Timer::getTimer1(), SIGNAL(timeout()), this, SLOT(createEnemyPlane()));
    connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(moveEnemy()));
//    scene->addItem(new EnemyBoss(1, "enemy0", this));
}

void GameController::addEnemy(int a)
{
    EnemyPlane *e = NULL;
    switch (a){
    case 1:
        e = Lists::getEnemyPlane(1);
        e->setPos(getRandomNumber(LENGTH-e->boundingRect().width()), 0);
        e->setParent(this);
        scene->addItem(e);
        currentEnemyPlaneList.append(e);
        break;
    case 2:
        e = Lists::getEnemyPlane(2);
        e->setPos(getRandomNumber(LENGTH-e->boundingRect().width()), 0);
        e->setParent(this);
        scene->addItem(e);
        currentEnemyPlaneList.append(e);
        break;
    }
    e->setObjectName("enemy"+QString::number(getRandomNumber(100)));
}

void GameController::addEnemyGroup(int a)
{
    if (!enemyPlaneGroupCreating){
        enemyPlaneGroupCount = 0;
        switch(a){
        case 1:
            connect(Timer::getTimer5(),
                    SIGNAL(timeout()),
                    this,
                    SLOT(addEnemyPlaneGroup1()));
            enemyPlaneGroupCreating = true;
            break;
        }
    }
    else {
        addEnemy(1);
    }
}

void GameController::createEnemyPlane()
{
    switch(getRandomNumber(9)){
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        addEnemy(1);
        break;
    case 6:
    case 7:
        addEnemy(2);
        break;
    case 8:
    case 9:
        addEnemyGroup(1);
        break;
    }
}

void GameController::moveEnemy()
{
    foreach (EnemyPlane *e, currentEnemyPlaneList){
        e->move();
        e->enemyCollisions();
        if (e->x()<0-e->boundingRect().width() || e->x()>LENGTH ||
            e->y()<0-e->boundingRect().height() || e->y()>HEIGHT){
            removeEnemy(e);
        }
        else if (e->getRemoveFlag()){
            score->addScore(e->getScore());
            scene->addItem(new Explosion(e->x()-10, e->y()-10, this));
            switch(getRandomNumber(30)){
            case 0:
                if (plane->getAttackType()!=Laser){
                    scene->addItem(new BuffItem(TurnToLaser, e->x(), e->y(), this));
                }
                break;
            case 1:
                if (plane->getAttackType()!=Bullet){
                    scene->addItem(new BuffItem(TurnToBullet, e->x(), e->y(), this));
                }
                break;
            case 3:
                scene->addItem(new BuffItem(LevelUp, e->x(), e->y(), this));
                break;
            case 4:
                scene->addItem(new BuffItem(AddMissile, e->x(), e->y(), this));
                break;
            case 5:case 6:case 7:case 8:case 9:case 10:case 11:
                scene->addItem(new BuffItem(Diamond, e->x(), e->y(), this));
                break;
            }
            removeEnemy(e);
        }
    }
}

void GameController::removeEnemy(EnemyPlane *e)
{
    currentEnemyPlaneList.removeOne(e);
    Lists::recoverEnemyPlane(e);
}

int GameController::getRandomNumber(int max)
{
     return rand()%(max+1);//随机产生一个0至max的随机数
}

void GameController::addEnemyPlaneGroup1()
{
    EnemyPlane *e = Lists::getEnemyPlane(3);
    setObjectName("enemy"+QString::number(getRandomNumber(100)));
    e->setPos(0, 0);
    e->setParent(this);
    scene->addItem(e);
    currentEnemyPlaneList.append(e);
    enemyPlaneGroupCount++;
    if (enemyPlaneGroupCount == 10){
        disconnect(Timer::getTimer5(),
                   SIGNAL(timeout()),
                   this,
                   SLOT(addEnemyPlaneGroup1()));
        enemyPlaneGroupCreating = false;
    }
}

QGraphicsScene* GameController::getScene()
{
    return scene;
}

void GameController::refreshPlayerHP(int a)
{
    if (a<=0){
        playerHP->playerDied();
    }
    playerHP->setHP(a);
}

void GameController::playerDestroyed(Plane *plane)
{
    scene->addItem(new Explosion(plane->x()-10, plane->y()-10, this));
    playerLife->decreaseLife();
    if (playerLife->getLife()>0){
        connect(Timer::getTimer1(), SIGNAL(timeout()), this, SLOT(createNewPlane()));
    }
}

void GameController::createNewPlane()
{
    plane = new Plane(this);
    playerHP->reset();
    disconnect(Timer::getTimer1(), SIGNAL(timeout()), this, SLOT(createNewPlane()));
}

void GameController::getScore(int a)
{
    score->addScore(a);
}

