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

    int getShells(){
        return shells;
    }

    bool isAlive(){
        return alive;
    }

    void selfDestruct(){
        alive = false;
        cout << "Robot " << getX()<<","<<getY() << " has been destroyed!" << endl;;
    }
    void takeDamage() {
        lives--;
        if (lives <= 0) {
            alive = false;
            cout << "Robot " << getX()<<","<<getY() << " has been destroyed!" << endl;
        } else {
            cout << "Robot " << getX()<<","<<getY() << " was hit! Lives left: " << lives << endl;
        }
    }
    void upgrade(){
        
    }
    int getLive(){
        return lives;
    }
};

Robot::~Robot() {}


