#pragma once
#include "Robot.h"

class ShootingRobot : virtual public Robot {
public:
    ShootingRobot(int startX = 0, int startY = 0) : Robot(startX, startY) {}
    virtual void fire(int dx, int dy) = 0;
};
