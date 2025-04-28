#pragma once
#include "Robot.h"

class ThinkingRobot : virtual public Robot {
public:
    ThinkingRobot(string name = "Default", int startX = 0, int startY = 0) : Robot(name, startX, startY) {}
    virtual void think(vector<vector<Robot*>>& battlefield) = 0;
};
