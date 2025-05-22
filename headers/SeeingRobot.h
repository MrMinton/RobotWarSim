#pragma once
#include "Robot.h"

class SeeingRobot : virtual public Robot {
public:
    using Robot :: Robot;
    virtual void look(vector<Robot*>& robots) = 0;
};
