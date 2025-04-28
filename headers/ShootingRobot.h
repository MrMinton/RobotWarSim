#pragma once
#include "Robot.h"

class ShootingRobot : virtual public Robot {
public:
    ShootingRobot(string name = "Default", int startX = 0, int startY = 0) : Robot(name, startX, startY) {}
    virtual void fire(int dx, int dy) = 0;
};
