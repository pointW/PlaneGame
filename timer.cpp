#include "timer.h"

QTimer* Timer::timer = NULL;
QTimer* Timer::timer1 = NULL;
QTimer* Timer::timer5 = NULL;
QTimer* Timer::timer2 = NULL;
QTimer* Timer::timer10 = NULL;

Timer::Timer()
{

}

QTimer* Timer::getTimer()
{
    if (timer == NULL){
        timer = new QTimer();
        timer->start(16);
    }
    return timer;
}

QTimer* Timer::getTimer1()
{
    if (timer1 == NULL){
        timer1 = new QTimer();
        timer1->start(1000/1);
    }
    return timer1;
}

QTimer* Timer::getTimer5()
{
    if (timer5 == NULL){
        timer5 = new QTimer();
        timer5->start(1000/5);
    }
    return timer5;
}

QTimer* Timer::getTimer2()
{
    if (timer2 == NULL){
        timer2 = new QTimer();
        timer2->start(1000/2);
    }
    return timer2;
}

QTimer* Timer::getTimer10()
{
    if (timer10 == NULL){
        timer10 = new QTimer();
        timer10->start(1000/10);
    }
    return timer10;
}
