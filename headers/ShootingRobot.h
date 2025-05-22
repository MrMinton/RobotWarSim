#pragma once
#include "Robot.h"

class ShootingRobot : virtual public Robot {
public:
    using Robot :: Robot;
    virtual void fire(vector<Robot*>& robots) = 0;
};
