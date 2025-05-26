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
        switch(0){
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
            return;
        }

        int newShells= getShells()-1;
        int targetX = dx + getX();
        int targetY = dy + getY();
        int hitprob = rand() % 100;

        if (targetX < 0 || targetX >= cols || targetY < 0 || targetY>=row){
            cout << "Out of bounds"<< endl;
        }
        if (hitprob < 70){
            for (Robot* r : robots) {
                if (r->isAlive() && r->getX() == targetX && r->getY() == targetY) {
                    r->takeDamage();
                    cout << "Hit"<<endl;
                    cout<< "Remaining shells = "<<newShells<<endl;
                    // upgrade function if r->isAlive == false{}
                    // performUpgrade()
                    break;
                    }
                else {
                    cout << "Miss"<<endl;
                    cout<< "Remaining shells = "<<newShells<<endl;
                    break;
                }
            }
        }
        else {
            cout << "Miss coz more than 70"<<endl;
            cout<< "Remaining shells = "<<newShells<<endl;
        }
    }
};

//Hidebot(){}


//performupgrade(){
// randomising stuff HIdebot HideBot();}