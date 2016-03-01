#include "drone.h"

Drone::Drone()
{
    visionWidth = 1.0;
}

Drone::Drone(double visionWidth)
{
    if(visionWidth > MIN_VISIONWIDTH)
        this->visionWidth = visionWidth;
    else
        this ->visionWidth = MIN_VISIONWIDTH;
}

Drone::~Drone()
{

}
