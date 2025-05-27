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

using namespace std;

class GenericRobot : public MovingRobot, public ShootingRobot, public SeeingRobot, public ThinkingRobot {

private:
    bool isHideBot = false;
    bool isJumpBot = false;
    bool isLongShotBot = false;
    bool isSemiAutoBot = false;
    bool isThirtyShotBot = false;
    bool isScoutBot = false;
    bool isTrackBot = false;

    int upgradesTaken = 0;
    bool upgradedMoving = false;
    bool upgradedShooting = false;
    bool upgradedSeeing = false;

    int hideCount = 0;
    bool isHiding = false;
    int jumpCount= 0;


public:

    GenericRobot(int x, int y) : Robot(x, y), MovingRobot(x, y), ShootingRobot(x, y), SeeingRobot(x, y), ThinkingRobot(x, y) {}

    void setHideBot(bool val) {
        isHideBot = val;
        if (val) hideCount = 3;
    }

    void reveal() {
        isHiding = false;

        if (hideCount <= 0) {
            isHideBot = false;
        }
    }

    bool currentlyHiding() const {
        return isHiding;
    }

    void hide() {
    if (!isHideBot) {
        return;
    }

    if (hideCount <= 0) {
        cout << "No hides left." << endl;
        return;
    }

    isHiding = true;
    hideCount--;
    cout << "Robot is now hiding. Hides left: " << hideCount << endl;
    }

    void setJumpBot(bool val) {
        isJumpBot = val;
        if (val) jumpCount = 3;
    }

    void jump(vector<Robot*>& robots) {
        if (!isJumpBot) {
            return;
        }

        if (jumpCount <= 0) {
            cout << "No jumps left." << endl;
            return;
        }

        int newX = rand() % cols;
        int newY = rand() % row;

        bool occupied = false;
        for (Robot* r : robots) {
            if (r->isAlive() && r->getX() == newX && r->getY() == newY) {
                occupied = true;
                break;
            }
        }

        if (!occupied) {
            setPosition(newX,newY);
            jumpCount--;
            cout << "Robot jumped to " << newX << ", " << newY << endl;
            return;
        }
        cout << "Jump unsucessful" << endl;
    }

    void setLongShotBot(bool val) {
        isLongShotBot = val;
    }

    void setSemiAutoBot(bool val) {
        isSemiAutoBot = val;
    }

    void setThirtyShotBot(bool val) {
        isThirtyShotBot = val;
    }

    void setScoutBot(bool val) {
        isScoutBot = val;
    }

    void setTrackBot(bool val) {
        isTrackBot = val;
    }

    void upgrade() {
        if (upgradesTaken >= 3){
            cout << "Max upgrades reached, goodjob." << endl;
            return;
        }

        vector<int> availableCategories;

        if (!upgradedMoving) availableCategories.push_back(0);
        if (!upgradedShooting) availableCategories.push_back(1);
        if (!upgradedSeeing) availableCategories.push_back(2);

        if(availableCategories.empty()) {
            return;
        }

        int choiceIndex = rand() % availableCategories.size();
        int chosenCategory = availableCategories[choiceIndex];

        switch(chosenCategory) {
            case 0: {  //for moving
                upgradedMoving = true;
                int moveChoice = rand() % 2;
                if(moveChoice == 0){
                    setHideBot(true);
                    cout << "Upgraded to HideBot" << endl;
                } else {
                    setJumpBot(true);
                    cout << "Upgraded to JumpBot" << endl;
                }
                break;
            }
            case 1: { //for shooting
                upgradedShooting = true;
                int moveChoice = rand() % 3;
                if(moveChoice == 0){
                    setLongShotBot(true);
                    cout << "Upgraded to LongShotBot" << endl;
                } else if(moveChoice == 1){
                    setSemiAutoBot(true);
                    cout << "Upgraded to SemiAutoBot" << endl;
                } else if(moveChoice == 2) {
                    setThirtyShotBot(true);
                    cout << "Upgraded to ThirtyShotBot " << endl;
                }
                break;
            }
            case 2: { //for seeing
                upgradedSeeing = true;
                int moveChoice = rand() % 2;
                if(moveChoice == 0){
                    setScoutBot(true);
                    cout << "Upgraded to ScoutBot" << endl;
                } else {
                    setTrackBot(true);
                    cout << "Upgraded to TrackBot " << endl;
                }
                break;
            }
        }
        upgradesTaken++;
    }


    virtual void think(vector<Robot*>& robots){
        reveal();
        
    if (wasHit()) {
        cout << "💥 Robot at (" << getX() << ", " << getY() << ") u r eliminated and skip action this turn.\n";

        int newX, newY, attempts = 0;
        do {
            newX = rand() % cols;
            newY = rand() % row;
            bool occupied = false;

            for (Robot* r : robots) {
                if (r != this && r->isAlive() && r->getX() == newX && r->getY() == newY) {
                    occupied = true;
                    break;
                }
            }

            if (!occupied) break;
            attempts++;
        } while (attempts < 10);

        setPosition(newX, newY); 
        cout << "💫 Robot respawned to new position (" << newX << ", " << newY << ")\n";  
        resetHit();
        return;  // skip the rest of the turn
    }

        while(true) {
            int rand_num = rand()%5;
            int decision = rand_num;
            switch(decision){
                case 0:
                    minusShells();
                    // for (Robot* r : robots) {
                    //     r->getShells();
                    // }
                    fire(robots);
                    return;
                case 1:
                    move(robots);
                    return;
                case 2:
                    look(robots);
                    return;
                case 3:
                    if(isHideBot){
                        hide();
                        return;
                    }  
                    break;                      
                case 4:
                    if(isJumpBot){
                        jump(robots);
                        return;
                    } 
                    break;                  
            }
        }       
    };

    virtual void move(vector<Robot*>& robots) {
         vector<pair<int,int>> directions ={
            {-1,-1}, {0,-1}, {1,-1},
            {-1,0},          {1,0},
            {-1,1}, {0,1}, {1,1}
        };

        int index = rand() % directions.size();
        int dx = directions[index].first;
        int dy = directions[index].second;

        int targetX = dx + getX();
        int targetY = dy + getY();

        if (dx == 0 && dy == 0) {
            cout << "Staying still is not considered a move!" << endl;
            return;
        }

        if (targetX < 0 || targetX >= cols || targetY < 0 || targetY >= row) {
            cout << "Cannot move out of bounds!" << endl;
            return;
        }

        // Check for collision with other robots
        for (Robot* r : robots) {
            if (r != this && r->isAlive() && r->getX() == targetX && r->getY() == targetY) {
                cout << "Cannot move to (" << targetX << ", " << targetY << ") - blocked by another robot at ("
                    << r->getX() << ", " << r->getY() << ")" << endl;
                return;
            }
        }
            setPosition(targetX, targetY);
         cout << "Moved to new position: (" << targetX << ", " << targetY << ")" << endl;
    };

    
    virtual void look(vector<Robot*>& robots) {
        vector<pair<int,int>> directions ={
            {-1,-1}, {0,-1}, {1,-1},
            {-1,0},          {1,0},
            {-1,1}, {0,1}, {1,1}
        };

        cout << "Looking around (" << getX() << ", " << getY() << "):" << endl;

        for (auto dir : directions) {
            int targetX = dir.first + getX();
            int targetY = dir.second + getY();

            if (targetX < 0 || targetX >= cols || targetY < 0 || targetY >= row) {
                cout << "Coordinate (" << targetX << ", " << targetY << ") is out of bounds." << endl;
                continue;
            }

            bool foundRobot = false;
            for (Robot* r : robots) {
                if (r->isAlive() && r->getX() == targetX && r->getY() == targetY) {
                    foundRobot = true;
                    break;
                }
            }

            if (foundRobot) {
                cout << "There's a robot at coordinate (" << targetX << ", " << targetY << ")." << endl;
            } else {
                cout << "Coordinate (" << targetX << ", " << targetY << ") is empty." << endl;
            }
        }
    };
    
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
        if (dx == 0 && dy == 0){
            cout << "Not allowed to kill urself";
            return;
        }

        int targetX = dx + getX();
        int targetY = dy + getY();
        int hitprob = rand() % 100;

        if (targetX < 0 || targetX >= cols || targetY < 0 || targetY>=row){
            cout << "Out of bounds"<< endl;
            return;
        }

        if (hitprob < 70){
            for (Robot* r : robots) {
                if (r->isAlive() && r->getX() == targetX && r->getY() == targetY) {
                    GenericRobot* gr = dynamic_cast<GenericRobot*>(r);
                    if (gr && gr->currentlyHiding()) {
                        cout << "🛡️ Target is hiding. Shot missed." << endl;
                        return;
                    }
                    cout << "Firing at (" << targetX << ", " << targetY << ")... "<<endl;
                    r->takeDamage();
                    cout << "Remaining Shells: "<< r->getShells() <<endl;
                    upgrade();                        
                    break;
                    }
                else{
                    cout<< "Miss"<<endl;
                    cout << "Remaining Shells: "<< r->getShells() <<endl;
                    break;
                }
            }
            }
        else {
            cout << "Miss coz more than 70"<<endl;
            cout << "Remaining Shells: "<< getShells() <<endl;
        }
    }
};


//performupgrade(){


//Hidebot(){}



// randomising stuff HIdebot HideBot();}