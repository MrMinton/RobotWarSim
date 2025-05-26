#pragma once

#include<iostream>
#include <vector>
using namespace std;

class Robot{
private:
    bool alive = true;
    string name;
    string type;
    int x, y;
    int lives =3;
    int shells =10;

public:
    Robot(){};
    Robot(int x_coord,int y_coord){
        x = x_coord;
        y = y_coord;
    }
    virtual ~Robot();

    int getX(){
        return x;
    }
    
    int getY(){
        return y;
    }

    int setPosition(int nX, int nY) {
        x = nX;
        y = nY;
    }

    string getName() {
        return name;
    }

    int getShells(){
        return shells;
    }

    bool isAlive(){
        return alive;
    }

    bool selfDestruct(){
        alive = false;
        lives--;
    }
    void takeDamage() {
        lives--;
        if (lives <= 0) {
            alive = false;
            cout << "Robot " << name << " has been destroyed!" << endl;
        } else {
            cout << "Robot " << name << " was hit! Lives left: " << lives << endl;
        }
    }
    // void upgrade(){
        
    // }
    int getLive(){
        return lives;
    }
};

Robot::~Robot() {}


