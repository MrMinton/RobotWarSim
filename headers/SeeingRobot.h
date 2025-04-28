#pragma once
#include "Robot.h"

class SeeingRobot : virtual public Robot {
public:
    SeeingRobot(string name = "Default", int startX = 0, int startY = 0) : Robot(name, startX, startY) {}
    virtual void look(int dx, int dy) = 0;
};
