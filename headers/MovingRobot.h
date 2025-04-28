#pragma once
#include "Robot.h"

class MovingRobot : virtual public Robot {
public:
    MovingRobot(string name = "Default", int startX = 0, int startY = 0) : Robot(name, startX, startY) {}
    virtual void move(int dx, int dy) = 0;
};
