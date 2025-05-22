#pragma once
#include "Robot.h"

class ThinkingRobot : virtual public Robot {
public:
    using Robot :: Robot;
    virtual void think(vector<Robot*>& robots) = 0;
};
