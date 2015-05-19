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

//bool GameController::eventFilter(QObject *object, QEvent *event)
//{
//    if (event->type() == QEvent::KeyPress) {
//        handleKeyPressed((QKeyEvent *)event);
//        return true;
//    }
//    else if (event->type() == QEvent::KeyRelease){
//        handleKeyRelease((QKeyEvent *)event);
//        return true;
//    }
//    else {
//        return QObject::eventFilter(object, event);
//    }
//}

//void GameController::handleKeyPressed(QKeyEvent *event)
//{
//    switch (event->key())
//    {
//    case Qt::Key_Left:
//        plane->moveLeft();
//        break;

//    case Qt::Key_Right:
//        plane->moveRight();
//        break;

//    case Qt::Key_Up:
//        plane->moveUp();
//        break;

//    case Qt::Key_Down:
//        plane->moveDown();
//        break;

//    case Qt::Key_Space:
//        plane->playerAttack();
//        break;

//    case Qt::Key_Q:
//        plane->shootMissile();
//    }
//}

//void GameController::handleKeyRelease(QKeyEvent *event)
//{
//    switch (event->key())
//    {
//    case Qt::Key_Left:
//        plane->stopLeft();
//        break;
//    case Qt::Key_Right:
//        plane->stopRight();
//        break;
//    case Qt::Key_Up:
//        plane->stopUp();
//        break;
//    case Qt::Key_Down:
//        plane->stopDown();
//        break;
//    case Qt::Key_Space:
//        plane->stopAttack();
//        break;

//    }
//}

void GameController::resume()
{
//    connect(Timer::getTimer1(), SIGNAL(timeout()), this, SLOT(createEnemyPlane()));
    scene->addItem(new EnemyBoss(1, "enemy0", this));
}

void GameController::addEnemy(int a)
{
    scene->addItem(new EnemyPlane(a, "enemy"+QString::number(getRandomNumber(100), 10), this));
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
                    SLOT(createEnemyPlaneGroup1()));
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

int GameController::getRandomNumber(int max)
{
     return rand()%(max+1);//随机产生一个0至max的随机数
}

void GameController::createEnemyPlaneGroup1()
{
    scene->addItem(new EnemyPlane(3, "enemy"+QString::number(getRandomNumber(100), 10), this));
    enemyPlaneGroupCount++;
    if (enemyPlaneGroupCount == 10){
        disconnect(Timer::getTimer5(),
                   SIGNAL(timeout()),
                   this,
                   SLOT(createEnemyPlaneGroup1()));
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

void GameController::enemyDestroyed(EnemyPlane *enemy)
{
    score->addScore(enemy->getScore());
    scene->addItem(new Explosion(enemy->x()-10, enemy->y()-10, this));
    switch(getRandomNumber(30)){
    case 0:
        if (plane->getAttackType()!=Laser){
            scene->addItem(new BuffItem(TurnToLaser, enemy->x(), enemy->y(), this));
        }
        break;
    case 1:
        if (plane->getAttackType()!=Bullet){
            scene->addItem(new BuffItem(TurnToBullet, enemy->x(), enemy->y(), this));
        }
        break;
    case 3:
        scene->addItem(new BuffItem(LevelUp, enemy->x(), enemy->y(), this));
        break;
    case 4:
        scene->addItem(new BuffItem(AddMissile, enemy->x(), enemy->y(), this));
        break;
    case 5:case 6:case 7:case 8:case 9:case 10:case 11:
        scene->addItem(new BuffItem(Diamond, enemy->x(), enemy->y(), this));
        break;
    }
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

