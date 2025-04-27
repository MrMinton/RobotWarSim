#pragma once
#include "Robot.h"

class ThinkingRobot : virtual public Robot {
public:
    ThinkingRobot(int startX = 0, int startY = 0) : Robot(startX, startY) {}
    virtual void think() = 0;
};
