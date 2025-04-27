#pragma once
#include "Robot.h"

class SeeingRobot : virtual public Robot {
public:
    SeeingRobot(int startX = 0, int startY = 0) : Robot(startX, startY) {}
    virtual void look(int dx, int dy) = 0;
};
