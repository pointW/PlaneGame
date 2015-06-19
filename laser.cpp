#include "laser.h"

Laser::Laser(QPixmap im, int w, int sh)
{
    image = im;
    width = w;
    singleHeight = sh;
}

Laser::~Laser()
{

}

void Laser::moveLaser()
{
    y+=15;
    if (y >= singleHeight){
        y = 0;
    }
    setPixmap(image.copy(0, y, width, HEIGHT));
}
