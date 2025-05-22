#pragma once
#include "Robot.h"

class MovingRobot : virtual public Robot {
public:
    using Robot :: Robot;
    virtual void move(vector<Robot*>& robots) = 0;
};
