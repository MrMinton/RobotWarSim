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
    bool hitlastturn = false;
    bool HitThisTurn = false;


public:
    void startNewTurn() { 
        hitlastturn = HitThisTurn;
        HitThisTurn = false;           
    }
    void resetHit(){
        
        hitlastturn = false;
    }
    bool RecentlyHit() const { 
        return hitlastturn; 
    }
    bool wasHit(){
        return HitThisTurn;
    }

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

    void setPosition(int nX, int nY) {
        x = nX;
        y = nY;
    }

    string getName() {
        return name;
    }

    void setType(string t){
        type = t;
    }

    string getType() {
        return type;
    }

    int getShells(){
        return shells;
    }
    
    void minusShells(){
        --shells;
    }

    bool isAlive(){
        return alive;
    }

    void selfDestruct(){
        alive = false;
        lives--;
    }
    
    void takeDamage() {
        lives--;
        HitThisTurn = true;
        if (lives <= 0) {
            alive = false;
            cout << "Robot " << getX()<<","<<getY() << " has been destroyed!" << endl;
        } else {
            cout << "Robot " << getX()<<","<<getY() << " was hit! Lives left: " << lives << endl;
        }
    }
    // void upgrade(){
        
    // }
    int getLive(){
        return lives;
    }
};

Robot::~Robot() {}


