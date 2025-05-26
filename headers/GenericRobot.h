#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "MovingRobot.h"
#include "ShootingRobot.h"
#include "SeeingRobot.h"
#include "ThinkingRobot.h"
#include "Robot.h"

int row,cols;
int robot_amount;
int steps;

using namespace std;

class GenericRobot : public MovingRobot, public ShootingRobot, public SeeingRobot, public ThinkingRobot {
public:

    GenericRobot(int x, int y) : Robot(x, y), MovingRobot(x, y), ShootingRobot(x, y), SeeingRobot(x, y), ThinkingRobot(x, y) {}
    virtual void think(vector<Robot*>& robots){
        int rand_num = rand()%3;
        int decision = rand_num;
        switch(decision){
            case 0:
                fire(robots);
                break;
            case 1:
                move(robots);
                break;
            case 2:
                look(robots);
                break;
        }

    };
    virtual void move(vector<Robot*>& robots) {};
    virtual void look(vector<Robot*>& robots) {};
    
    virtual void fire(vector<Robot*>& robots) {
        vector<pair<int,int>> directions ={
            {-1,-1}, {0,-1}, {1,-1},
            {-1,0},          {1,0},
            {-1,1}, {0,1}, {1,1}
        };

        int index = rand() % directions.size();
        int dx = directions[index].first;
        int dy = directions[index].second;

        if (getShells()<=0){
            cout << "Out of shells byebye!"<<endl;
            selfDestruct();
        }
        else{
            cout<< "Getshell problem"<<endl;
        }
        if (dx == 0 && dy == 0){
            cout << "Not allowed to kill urself";
            return;
        }
        else{
            cout << "Not allowed to kill urself problem"<<endl;
        }

        int targetX = dx + getX();
        int targetY = dy + getY();

        if (targetX < 0 || targetX >= cols || targetY < 0 || targetY>=row){
            cout << "Out of bounds"<< endl;
        }
        else{
            cout<<"Out of bounds problem"<<endl;
        }
        int hitprob = rand() % 100;
        
        if (hitprob < 70){
            for (Robot* r : robots) {
                if (r->isAlive() && r->getX() == targetX && r->getY() == targetY) {
                    r->takeDamage();
                    cout << "Hit"<<endl;
                    // upgrade function if r->isAlive == false{}
                    // performUpgrade()
                    break;
                    }
                }
            }
        else {
            cout << "Miss"<<endl;
        }
    }
};

//Hidebot(){}


//performupgrade(){
// randomising stuff HIdebot HideBot();}