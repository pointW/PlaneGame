#ifndef LASER_H
#define LASER_H

#include "flyitem.h"

class Laser:public FlyItem
{
    Q_OBJECT
public:
    Laser(QPixmap im, int w, int sh);
    ~Laser();
public slots:
    void moveLaser();
protected:
    QPixmap image;
    int y;
    int width;
    int singleHeight;
};

#endif // LASER_H
