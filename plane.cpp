#include <QDebug>
#include "plane.h"

#include <cmath>
#include <iostream>

using namespace std;

Plane::Plane(GameController *game)
{
    plane1 = QPixmap(":/images/player1");
    plane2 = QPixmap(":/images/player2");
    plane3 = QPixmap(":/images/player3");
    plane4 = QPixmap(":/images/player4");
    plane5 = QPixmap(":/images/player5");
    setData(GD_Type, GO_PlayerPlane);
    setObjectName("player");
    setPixmap(plane3);
    setParent(game);
    scene = game->getScene();
    scene->addItem(this);
    scene->installEventFilter(this);
    gameController = game;
    setX(300);
    setY(700);
    setZValue(1);
    HP = 100;
    LeftFlag = false;
    RightFlag = false;
    UpFlag = false;
    DownFlag = false;
    bulletFlag = false;
    laserFlag = false;
    missileFlag = false;
    attackFlag = false;
    visiable = true;
    beatable = false;

    attackType = Bullet;
    attackLevel = 1;
    missileLevel = 1;
    unbeatableTimes = 0;
    slopFlag = 0;
    transformImagesFlag = 0;
    superFlag = false;
    transformingFlag = false;

    connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(playerCollisions()));
    connect(this, &Plane::refreshHP, game, &GameController::refreshPlayerHP);
    connect(this, &Plane::playerDestroyed, game, &GameController::playerDestroyed);
    connect(Timer::getTimer5(), SIGNAL(timeout()), this, SLOT(playerUnbeatable()));
    connect(this, &Plane::getScore, game, &GameController::getScore);
    connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(moveBullet()));
    connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(moveMissile()));
    laser = new PlayerLaser(this);
}

Plane::~Plane()
{

}

void Plane::handleSlop()
{
    if (!superFlag){
        switch (slopFlag){
        case -4:
            setPixmap(plane1);
            break;
        case -2:
            setPixmap(plane2);
            break;
        case 0:
            setPixmap(plane3);
            break;
        case 2:
            setPixmap(plane4);
            break;
        case 4:
            setPixmap(plane5);
            break;
        }
    }
    else{
        switch (slopFlag){
        case -4:
            setPixmap(QPixmap(":/images/playerSuper1"));
            break;
        case -2:
            setPixmap(QPixmap(":/images/playerSuper2"));
            break;
        case 0:
            setPixmap(QPixmap(":/images/playerSuper3"));
            break;
        case 2:
            setPixmap(QPixmap(":/images/playerSuper4"));
            break;
        case 4:
            setPixmap(QPixmap(":/images/playerSuper5"));
            break;
        }
    }
}

void Plane::backToStraight()
{
    if (slopFlag<0){
        slopFlag++;
        handleSlop();
    }
    else if (slopFlag>0){
        slopFlag--;
        handleSlop();
    }
    else {
        disconnect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(backToStraight()));
    }
}

void Plane::posChangeLeft()
{
    if (x()>0){
        setX(x()-10);
        emit playerMoved(Left);
    }
    if (slopFlag>-4 && !transformingFlag){
        slopFlag--;
        handleSlop();
    }
}

void Plane::posChangeRight()
{
    if (x()<LENGTH-boundingRect().width()){
        setX(x()+10);
        emit playerMoved(Right);
    }
    if (slopFlag<4 && !transformingFlag){
        slopFlag++;
        handleSlop();
    }
}

void Plane::posChangeUp()
{
    if (y()>0){
        setY(y()-10);
        emit playerMoved(Up);
    }
}

void Plane::posChangeDown()
{
    if (y()<HEIGHT-boundingRect().height()){
        setY(y()+10);
        emit playerMoved(Down);
    }
}

void Plane::addBullet(int x, int y, int d)
{
    PlayerBullet *b = Lists::getPlayerBullet();
    b->setPos(x, y);
    b->setDirection(d);
    b->setParent(this);
    QGraphicsItem::scene()->addItem(b);
    currentPlayerBulletList.append(b);
}

void Plane::addMissile(int x, int y, double a)
{
    PlayerMissile *m = Lists::getPlayerMissile();
    m->setPos(x, y);
    m->setAngle(a);
    m->setParent(this);
    QGraphicsItem::scene()->addItem(m);
    currentPlayerMissileList.append(m);
}

void Plane::removeBullet(PlayerBullet *b)
{
    currentPlayerBulletList.removeOne(b);
    Lists::recoverPlayerBullet(b);
}

void Plane::removeMissile(PlayerMissile *m)
{
    currentPlayerMissileList.removeOne(m);
    Lists::recoverPlayerMissile(m);
}

void Plane::createBullet()
{
    switch (attackLevel){
    case 1:
        addBullet(x()+(boundingRect().width()-BULLETWIDTH)/2, y(), 3);
        break;
    case 2:
        addBullet(x()+(boundingRect().width()-BULLETWIDTH)/2-10, y(), 3);
        addBullet(x()+(boundingRect().width()-BULLETWIDTH)/2+10, y(), 3);
        break;
    case 3:
        addBullet(x()+(boundingRect().width()-BULLETWIDTH)/2, y(), 2);
        addBullet(x()+(boundingRect().width()-BULLETWIDTH)/2, y(), 3);
        addBullet(x()+(boundingRect().width()-BULLETWIDTH)/2, y(), 4);
        break;
    case 4:
        addBullet(x()+(boundingRect().width()-BULLETWIDTH)/2, y(), 1);
        addBullet(x()+(boundingRect().width()-BULLETWIDTH)/2, y(), 2);
        addBullet(x()+(boundingRect().width()-BULLETWIDTH)/2, y(), 3);
        addBullet(x()+(boundingRect().width()-BULLETWIDTH)/2, y(), 4);
        addBullet(x()+(boundingRect().width()-BULLETWIDTH)/2, y(), 5);
        break;
    }
}

void Plane::createMissile()
{
    switch (missileLevel){
    case 0:
        break;
    case 1:
        addMissile(x()+(boundingRect().width()-MISSILEWIDTH)/2, y(), 0);
    }
}

void Plane::moveBullet()
{
    foreach (PlayerBullet *b, currentPlayerBulletList){
        b->move();
        if (b->x()<0-b->boundingRect().width() || b->x()>LENGTH ||
            b->y()<0-b->boundingRect().height() || b->y()>HEIGHT){
            removeBullet(b);
        }
        else if (b->getRemoveFlag()){
            removeBullet(b);
        }
    }
}

void Plane::moveMissile()
{
    foreach (PlayerMissile *m, currentPlayerMissileList){
        m->changeAngleAndPos();
        if (m->x()<0-m->boundingRect().width() || m->x()>LENGTH ||
            m->y()<0-m->boundingRect().height() || m->y()>HEIGHT){
            removeMissile(m);
        }
        else if (m->getRemoveFlag()){
            removeMissile(m);
        }
    }
}

void Plane::playerAttack()
{
    attackFlag = true;
    switch(attackType){
    case Bullet:
        attackWithBullet();
        break;
    case Laser:
        attackWithLaser();
        break;
    }
    attackWithMissile();
}

void Plane::attackWithBullet()
{
    if (!bulletFlag){
        connect(Timer::getTimer5(), SIGNAL(timeout()), this, SLOT(createBullet()));
        bulletFlag = true;
    }
}

void Plane::attackWithLaser()
{
    if (!laserFlag){
        scene->addItem(laser);
        laserFlag = true;
    }
}

void Plane::stopAttack()
{
    attackFlag = false;
    if(bulletFlag){
        disconnect(Timer::getTimer5(), SIGNAL(timeout()), this, SLOT(createBullet()));
        bulletFlag = false;
    }
    if(laserFlag){
        scene->removeItem(laser);
        laserFlag = false;
    }
    if (missileFlag){
        disconnect(Timer::getTimer2(), SIGNAL(timeout()), this, SLOT(createMissile()));
        missileFlag = false;
    }
}

void Plane::moveLeft()
{
    if (!LeftFlag){
        connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(posChangeLeft()));
        LeftFlag = true;
    }
}

void Plane::moveRight()
{
    if (!RightFlag){
        connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(posChangeRight()));
        RightFlag = true;
    }
}

void Plane::moveUp()
{
    if (!UpFlag){
        connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(posChangeUp()));
        UpFlag = true;
    }
}

void Plane::moveDown()
{
    if (!DownFlag){
        connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(posChangeDown()));
        DownFlag = true;
    }
}

void Plane::stopLeft()
{
    disconnect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(posChangeLeft()));
    LeftFlag = false;
}

void Plane::stopRight()
{
    disconnect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(posChangeRight()));
    RightFlag = false;
}

void Plane::stopUp()
{
    disconnect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(posChangeUp()));
    UpFlag = false;
}

void Plane::stopDown()
{
    disconnect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(posChangeDown()));
    DownFlag = false;
}

void Plane::playerCollisions()
{
    collisions = collidingItems();
    foreach (QGraphicsItem *collidingItem, collisions) {
        if (collidingItem->data(GD_Type) == GO_BuffItem){
            BuffItem *bf = dynamic_cast<BuffItem*>(collidingItem);
            switch(bf->getBuffType()){
            case TurnToLaser:
                attackType = Laser;
                if(attackFlag){
                    stopAttack();
                    playerAttack();
                }
                break;
            case TurnToBullet:
                attackType = Bullet;
                if(attackFlag){
                    stopAttack();
                    playerAttack();
                }
                break;
            case LevelUp:
                if(attackLevel<4){
                    attackLevel++;
                    emit levelUp(attackLevel);
                }
                if(attackFlag){
                    stopAttack();
                    playerAttack();
                }
                break;
            case AddMissile:
                if (missileLevel<1){
                    missileLevel++;
                }
                if(attackFlag){
                    stopAttack();
                    playerAttack();
                }
                break;
            case Diamond:
                emit getScore(50);
                break;
            }
            bf->deleteLater();
        }
        else if (collidingItem->data(GD_Type) == GO_EnemyPlane){
            EnemyPlane *enemy = dynamic_cast<EnemyPlane *>(collidingItem);
            enemy->setRemoveFlag(true);
            if (beatable && !superFlag){
                HP-=10;
                emit refreshHP(HP);
                if(HP<=0){
                    emit playerDestroyed(this);
                    deleteLater();
                }
            }
        }
    }
}

AttackType Plane::getAttackType()
{
    return attackType;
}

void Plane::attackWithMissile()
{
    if (!missileFlag){
        connect(Timer::getTimer2(), SIGNAL(timeout()), this, SLOT(createMissile()));
        missileFlag = true;
    }
}

void Plane::handleKeyPressed(QKeyEvent *event)
{
    qDebug()<<children().count();
    switch (event->key())
    {
    case Qt::Key_Left:
        disconnect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(backToStraight()));
        moveLeft();
        break;

    case Qt::Key_Right:
        disconnect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(backToStraight()));
        moveRight();
        break;

    case Qt::Key_Up:
        moveUp();
        break;

    case Qt::Key_Down:
        moveDown();
        break;

    case Qt::Key_Space:
        playerAttack();
        break;

    case Qt::Key_Q:
        createMissile();
        break;

    case Qt::Key_W:
        transformToSuper();
        break;

    case Qt::Key_E:
        transformToNormal();
        break;

    case Qt::Key_R:
        Wingman *l = new Wingman(x()-20-WINGMANWIDTH, y()+30, 1, "wingmanLeft", this);
        Wingman *r = new Wingman(x()+20+PLAYERWIDTH, y()+30, 2, "wingmanRight", this);
        scene->addItem(l);
        scene->addItem(r);
        wingmanFlag = true;
    }
}

void Plane::handleKeyRelease(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        stopLeft();
        connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(backToStraight()));
        break;
    case Qt::Key_Right:
        stopRight();
        connect(Timer::getTimer(), SIGNAL(timeout()), this, SLOT(backToStraight()));
        break;
    case Qt::Key_Up:
        stopUp();
        break;
    case Qt::Key_Down:
        stopDown();
        break;
    case Qt::Key_Space:
        stopAttack();
        break;

    }
}

bool Plane::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        handleKeyPressed((QKeyEvent *)event);
        return true;
    }
    else if (event->type() == QEvent::KeyRelease){
        handleKeyRelease((QKeyEvent *)event);
        return true;
    }
    else {
        return QObject::eventFilter(object, event);
    }
}

void Plane::playerUnbeatable()
{
    visiable = !visiable;
    setVisible(visiable);
    unbeatableTimes++;
    if (unbeatableTimes>=15){
        disconnect(Timer::getTimer5(), SIGNAL(timeout()), this, SLOT(playerUnbeatable()));
        beatable = true;
        visiable = true;
        setVisible(visiable);
    }
}

void Plane::changeImageToSuper()
{
    if (transformImagesFlag<7){
        transformImagesFlag++;
        setTransformationImages();
        if (wingmanFlag){
            findChild<Wingman *>("wingmanRight")->setX(x()+20+boundingRect().width());
        }
    }
    else if(transformImagesFlag==7){
        disconnect(Timer::getTimer10(), SIGNAL(timeout()), this, SLOT(changeImageToSuper()));
        transformingFlag = false;
        superFlag = true;
        connect(Timer::getTimer2(), SIGNAL(timeout()), this, SLOT(superState()));
    }
}

void Plane::changeImageToNormal()
{
    if (transformImagesFlag>0){
        transformImagesFlag--;
        setTransformationImages();
        if (wingmanFlag){
            findChild<Wingman *>("wingmanRight")->setX(x()+20+boundingRect().width());
        }
    }
    else if(transformImagesFlag==0){
        disconnect(Timer::getTimer10(), SIGNAL(timeout()), this, SLOT(changeImageToNormal()));
        transformingFlag = false;
        superFlag = false;
    }
}

void Plane::setTransformationImages()
{
    switch (transformImagesFlag){
    case 0:
        setPixmap(QPixmap(":/images/player3"));
        break;
    case 1:
        setPixmap(QPixmap(":/images/transform1"));
        break;
    case 2:
        setPixmap(QPixmap(":/images/transform2"));
        break;
    case 3:
        setPixmap(QPixmap(":/images/transform3"));
        break;
    case 4:
        setPixmap(QPixmap(":/images/transform4"));
        break;
    case 5:
        setPixmap(QPixmap(":/images/transform5"));
        break;
    case 6:
        setPixmap(QPixmap(":/images/transform6"));
        break;
    case 7:
        setPixmap(QPixmap(":/images/playerSuper3"));
        break;
    }
}

void Plane::transformToSuper()
{
    if (!superFlag && !transformingFlag){
        transformImagesFlag = 0;
        connect(Timer::getTimer10(), SIGNAL(timeout()), this, SLOT(changeImageToSuper()));
        transformingFlag = true;
    }
}

void Plane::transformToNormal()
{
    if (superFlag && !transformingFlag){
        transformImagesFlag = 7;
        connect(Timer::getTimer10(), SIGNAL(timeout()), this, SLOT(changeImageToNormal()));
        transformingFlag = true;
    }
}

void Plane::superState()
{
//    if (superFlag){
//        scene->addItem(new PlayerMissile(x()+(boundingRect().width()-MISSILEWIDTH)/2, y(), 0, this));
////        scene->addItem(new PlayerMissile(x()+(boundingRect().width()-MISSILEWIDTH)/2, y(), 15, this));
////        scene->addItem(new PlayerMissile(x()+(boundingRect().width()-MISSILEWIDTH)/2, y(), -15, this));
//        scene->addItem(new PlayerMissile(x()+(boundingRect().width()-MISSILEWIDTH)/2, y(), 30, this));
//        scene->addItem(new PlayerMissile(x()+(boundingRect().width()-MISSILEWIDTH)/2, y(), -30, this));
////        scene->addItem(new PlayerMissile(x()+(boundingRect().width()-MISSILEWIDTH)/2, y(), 45, this));
////        scene->addItem(new PlayerMissile(x()+(boundingRect().width()-MISSILEWIDTH)/2, y(), -45, this));
//        scene->addItem(new PlayerMissile(x()+(boundingRect().width()-MISSILEWIDTH)/2, y(), 60, this));
//        scene->addItem(new PlayerMissile(x()+(boundingRect().width()-MISSILEWIDTH)/2, y(), -60, this));
////        scene->addItem(new PlayerMissile(x()+(boundingRect().width()-MISSILEWIDTH)/2, y(), 75, this));
////        scene->addItem(new PlayerMissile(x()+(boundingRect().width()-MISSILEWIDTH)/2, y(), -75, this));
//        scene->addItem(new PlayerMissile(x()+(boundingRect().width()-MISSILEWIDTH)/2, y(), 90, this));
//        scene->addItem(new PlayerMissile(x()+(boundingRect().width()-MISSILEWIDTH)/2, y(), -90, this));
//    }
//    else {
//        disconnect(Timer::getTimer2(), SIGNAL(timeout()), this, SLOT(superState()));
//    }
}

//void Plane::moveWingmanFront()
//{
//    switch (wingmanMoveFlag){
//    case 1:
//        findChild<Wingman *>("wingmanLeft")->setX(x());
//        findChild<Wingman *>("wingmanLeft")->setY(y());
//        findChild<Wingman *>("wingmanRight")->setX(x()+12);
//        break;
//    case 2:
//        findChild<Wingman *>("wingmanLeft")->setX(x());

//    }
//}





