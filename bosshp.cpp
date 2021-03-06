#include "bosshp.h"

BossHP::BossHP(EnemyBoss *boss, int maxHP)
{
    setParent(boss);
    white = new QGraphicsPixmapItem();
    red = new QGraphicsPixmapItem();
    white->setZValue(10);
    red->setZValue(11);
    white->setPixmap(QPixmap(":/images/bossHP1"));
    redPixmap = QPixmap(":/images/bossHP2");
    red->setPixmap(redPixmap.copy(0, 0, 500-4, 20-4));
    white->setPos(50, 50);
    red->setPos(50+2, 50+2);
    max = maxHP;
    setVisiable(false);
}

BossHP::~BossHP()
{

}

void BossHP::setHP(double HP)
{
    red->setPixmap(redPixmap.copy(0, 0, 500*(HP/max)-4, 20-4));
}

void BossHP::setVisiable(bool b)
{
    white->setVisible(b);
    red->setVisible(b);
}

void BossHP::addToScene(QGraphicsScene *s)
{
    s->addItem(white);
    s->addItem(red);
}
