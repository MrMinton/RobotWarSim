#pragma once

#include<iostream>
using namespace std;

class Robot {
private:
    int x, y;

protected:
    void setPosition(int newX, int newY) {
        x = newX;
        y = newY;
    }

public:
    Robot (int startX = 0, int startY = 0) : x(startX), y(startY) {}
    virtual ~Robot() {}

    int getX() const {return x;}
    int getY() const {return y;}

    virtual void look (int dx, int dy) = 0;
    virtual void move (int dx, int dy) = 0;
    virtual void fire (int dx, int dy) = 0;
    virtual void think () = 0;

};


