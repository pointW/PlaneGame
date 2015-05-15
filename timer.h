#ifndef TIMER_H
#define TIMER_H

#include <QTimer>

class Timer
{
private:
    Timer();
    static QTimer *timer;
    static QTimer *timer1;
    static QTimer *timer5;
    static QTimer *timer2;
    static QTimer *timer10;
public:
    static QTimer* getTimer();
    static QTimer* getTimer1();
    static QTimer* getTimer5();
    static QTimer* getTimer2();
    static QTimer* getTimer10();
};



#endif // TIMER_H
