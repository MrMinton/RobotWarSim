#pragma once

#include<iostream>
#include <vector>
using namespace std;

class Robot {
private:
    int x, y;
    string name;

protected:
    void setPosition(int newX, int newY) {
        x = newX;
        y = newY;
    }

public:
    Robot (string robotName = "Default", int startX = 0, int startY = 0) : name(robotName), x(startX), y(startY) {}

    virtual ~Robot() {}

    int getX() const {return x;}
    int getY() const {return y;}

    string getName() const {
        return name;
    }

    virtual void look (int dx, int dy) = 0;
    virtual void move (int dx, int dy) = 0;
    virtual void fire (int dx, int dy) = 0;
    virtual void think (vector<vector<Robot*>>& battlefield) = 0;

};


