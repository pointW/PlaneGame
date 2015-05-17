#include "flyitem.h"

FlyItem::FlyItem()
{

}

FlyItem::~FlyItem()
{

}

int FlyItem::getRandomNumber(int max)
{
     return rand()%(max+1);//随机产生一个0至max的随机数
}
