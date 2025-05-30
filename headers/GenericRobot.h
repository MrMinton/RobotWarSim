#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Battlefield.h"  
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
    int scoutCount = 0;
    int trackCount = 0;
    vector<Robot*> trackedRobots;


public:

    static Battlefield* battlefieldPtr;
    GenericRobot(int x, int y) : Robot(x, y), MovingRobot(x, y), ShootingRobot(x, y), SeeingRobot(x, y), ThinkingRobot(x, y) {}


    void setHideBot(bool val) {
        isHideBot = val;
        setType("HideBot");
        if (val) hideCount = 3;
    }

    void reveal() {
        isHiding = false;
        if (hideCount <= 0) {
            isHideBot = false;
        } else if(jumpCount <= 0){
            isJumpBot = false;
        } else if (scoutCount <= 0){
            isScoutBot = false;
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
        setType("JumpBot");
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
        setType("LongShotBot");
    }

    void longShot(vector<Robot*>& robots) {
        if (!isLongShotBot) {
            return;
        }

        vector<pair<int, int>> directions;

        for (int dx = -3; dx <= 3; ++dx) {
            for (int dy = -3; dy <= 3; ++dy) {
                if (dx == 0 && dy == 0) continue;
                if (abs(dx) + abs(dy) <= 3)
                    directions.push_back({dx, dy});
            }
        }

        if (getShells() <= 0) {
            cout << "Out of shells byebye!" << endl;
            selfDestruct();
            return;
        }

        cout << "Long Shot activated!" << endl;

        int index = rand() % directions.size();
        int dx = directions[index].first;
        int dy = directions[index].second;

        int targetX = dx + getX();
        int targetY = dy + getY();
        int hitprob = rand() % 100;

        if (targetX < 0 || targetX >= cols || targetY < 0 || targetY >= row) {
            cout << "Out of bounds. Therefore, bullet wasted" << endl;
            return;
        }

        if (hitprob < 70) {
            bool targetFound = false;
            for (Robot* r : robots) {
                if (r->isAlive() && r->getX() == targetX && r->getY() == targetY) {
                    targetFound = true;
                    GenericRobot* gr = dynamic_cast<GenericRobot*>(r);
                    if (gr && gr->currentlyHiding()) {
                        cout << "🛡️ Target is hiding. Shot missed." << endl;
                        cout << "Remaining Shells: " << getShells() << endl;
                        return;
                    } else {
                        cout << "Long Shotting at (" << targetX << ", " << targetY << ")... " << endl;
                        r->takeDamage();
                        cout << "🎯 Long Shot Hit!" << endl;
                        cout << "Remaining Shells: " << getShells() << endl;
                        if (isAlive()) {
                            upgrade();
                        }
                        break;
                    }                    
                }
            }
            if (!targetFound) {
                cout << "Miss no robot found at (" << targetX << ", " << targetY << ")" << endl;
                cout << "Remaining Shells: "<< getShells() <<endl;
            }
        } else {
            cout << "Miss coz more than 70, unlucky." << endl;
            cout << "Remaining Shells: " << getShells() << endl;
        }
    }

    void setSemiAutoBot(bool val) {
        isSemiAutoBot = val;
        setType("SemiAutoBot");
    }

    void semiAutoShot(vector<Robot*>& robots) {

        if (!isSemiAutoBot) {
            return;
        }

        vector<pair<int,int>> directions = {
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

        if (targetX < 0 || targetX >= cols || targetY < 0 || targetY>=row) {
            cout << "Out of bounds. Therefore, bullet wasted"<< endl;
            return;
        }

        cout << "SemiAutoShot Activated" << endl;

        bool targetFound = false;
        for (Robot* r : robots) {
            if (r->isAlive() && r->getX() == targetX && r->getY() == targetY) {
                targetFound = true;
                GenericRobot* gr = dynamic_cast<GenericRobot*>(r);
                if (gr && gr->currentlyHiding()) {
                    cout << "🛡️ Target is hiding. Shot missed." << endl;
                } else {
                    for(int i = 0; i < 3 && r->isAlive(); ++i) {
                        int hitProb = rand() % 100;
                        cout << "SemiAutoShot at (" << targetX << ", " << targetY << ")... " << endl;
                        if(hitProb < 70) {
                            r->takeDamage();
                            cout << "🎯SemiAutoShot Hit!" << endl;
                            if (isAlive()) {
                            upgrade();
                            }
                            break;
                        } else {
                            cout << "Miss SemiAutoShot" << endl;
                        }                   
                    }
                }
                break;                
            }             
        } 
        if (!targetFound) {
            cout << "Miss no robot found at (" << targetX << ", " << targetY << ")" << endl;
        }
        cout << "Remaining Shells: " << getShells() << endl;
    }

    void setThirtyShotBot(bool val) {
        isThirtyShotBot = val;
        setType("ThirtyShotBot");
    }
    void thirtyShotBot(vector<Robot*>& robots){
        for (Robot* r: robots){
            thirtyShells();
        }
    }
    void setScoutBot(bool val) {
        isScoutBot = val;
        setType("ScoutBot");
        if (val){
            scoutCount =3;
        }
    }

    void scoutbot(vector<Robot*>& robots) {
        if (!isScoutBot || battlefieldPtr == nullptr) return;

        if (scoutCount <= 0) {
            cout << "🛑 ScoutBot ability used up! No more uses left.\n";
            return;
        }

        scoutCount--;  // use one charge

        battlefieldPtr->refresh(robots);  // ✅ Update battlefield to current state

        cout << "🛰️ ScoutBot Activated! Battlefield overview:\n";

        for (int y = 0; y < row; y++) {
            for (int x = 0; x < cols; x++) {
                cout << battlefieldPtr->a2d[y][x] << " ";
            }
            cout << endl;
        }
    }


    void setTrackBot(bool val) {
        isTrackBot = val;
        setType("TrackBot");
        if (val){
            trackCount = 3;
        }
    }

    void trackBot(vector<Robot*>& robots){

        if (!isTrackBot) {
            return;
        }

        if (trackCount <= 0) {
            cout << "No tracks left." << endl;
            return;
        }

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
            cout << "Coordinate (" << targetX << ", " << targetY << ") is out of bounds." << endl;

        }

        bool foundRobot = false;
        for (Robot* r : robots) {
            if (r->isAlive() && r->getX() == targetX && r->getY() == targetY) {
                foundRobot = true;
                cout << "👀 Robot spotted at (" << targetX << ", " << targetY << ")." << endl;

                if (find(trackedRobots.begin(), trackedRobots.end(), r) == trackedRobots.end()) {
                    trackedRobots.push_back(r);
                    trackCount--;
                    cout << "📍 Tracker planted. Trackers left: " << trackCount << endl;                        
                } else if (trackCount == 0) {
                    cout << "🔁 Already tracking this robot." << endl;
                }

                break; 
            }
        }

        if (!foundRobot) {
            cout << "Coordinate (" << targetX << ", " << targetY << ") is empty." << endl;
        }
    }

    void displayTrackedRobots() {
        cout << endl;
        cout << "📡 Currently Tracked Robots:" << endl;
        for (Robot* r : trackedRobots) {
            if (r->isAlive()) {
                cout << "Robot at (" << r->getX() << ", " << r->getY() << ")" << endl;
            } else {
                cout << "Robot previously tracked at (" << r->getX() << ", " << r->getY() << ") was destroyed" << endl;
            }
        }
    }

    void upgrade() {

        cout << "Attempting Upgrade" << endl;

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
                int moveChoice = rand() % 2;
                if(moveChoice == 0){
                    setLongShotBot(true);
                    cout << "Upgraded to LongShotBot" << endl;
                } else if(moveChoice == 1){
                    setSemiAutoBot(true);
                    cout << "Upgraded to SemiAutoBot" << endl;
                } else if(moveChoice == 2) {
                    thirtyShells();
                    cout << "Upgraded to ThirtyShotBot " << endl;
                }
                break;
            }
            case 2: { //for seeing
                upgradedSeeing = true;
                int moveChoice = 0;
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
        
        if(isTrackBot){
            displayTrackedRobots();
        }
        
        reveal();

        if (wasHit()) {
            cout << endl ;
            cout << "💥 Robot at (" << getX() << ", " << getY() << ") u r eliminated and skip action this turn.\n";
            return;  // skip the rest of the turn
        }
        if (RecentlyHit()) {

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

            cout << endl;
            // cout << "💥 Robot at (" << getX() << ", " << getY() << ") is eliminated last turn.\n";
            setPosition(newX, newY);
            cout << endl;
            cout << "💫 Robot respawned to new position (" << newX << ", " << newY << ")\n";  
            resetHit();
            }
        cout << "\n🤖 Robot at (" << getX() << ", " << getY() << ") is taking its turn...\n";
        

        while(true) {
            int rand_num = rand() % 10;
            int decision = rand_num;
            switch(decision){
                case 0:
                    cout << "Attempting Fire" << endl;
                    minusShells();
                    for (Robot* r : robots) {
                        r->getShells();
                    }
                    fire(robots);
                    return;
                case 1:
                    cout << "Attempting Move" << endl;
                    move(robots);
                    return;
                case 2:
                    cout << "Attempting Look" << endl;
                    look(robots);
                    return;
                case 3:
                    if(isHideBot){
                        cout << "Attempting Hide" << endl;
                        hide();
                        return;
                    }  
                    break;                      
                case 4:
                    if(isJumpBot){
                        cout << "Attempting Jump" << endl;
                        jump(robots);
                        return;
                    } 
                    break;  
                case 5:
                    if(isLongShotBot){
                        cout << "Attempting Longshot" << endl;
                        minusShells();
                        longShot(robots);
                        return;
                    } 
                    break;
                case 6:
                    if(isSemiAutoBot){
                        cout << "Attempting SemiautoShot" << endl;
                        minusShells();
                        semiAutoShot(robots);
                        return; 
                    }
                    break;
                case 7:
                    if (isThirtyShotBot){
                        cout << "Replacing current shells with 30 Shells hehe" << endl;
                        thirtyShotBot(robots);
                        return;
                    }
                    break;
                case 8:
                    if(isScoutBot){
                        cout << "Attempting Scouting" << endl;
                        scoutbot(robots);
                        return;
                    }
                    break;
                case 9:
                    if(isTrackBot){
                        cout << "Attempting Tracking" << endl;
                        trackBot(robots);
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
            cout << "Out of bounds. Therefore, bullet wasted"<< endl;
            return;
        }

        if (hitprob < 70){
            bool targetFound = false;
            for (Robot* r : robots) {
                if (r->isAlive() && r->getX() == targetX && r->getY() == targetY) {
                    targetFound = true;
                    GenericRobot* gr = dynamic_cast<GenericRobot*>(r);
                    if (gr && gr->currentlyHiding()) {
                        cout << "🛡️ Target is hiding. Shot missed." << endl;
                        cout << "Remaining Shells: " << getShells() << endl;
                        return;
                    } else {
                        cout << "Firing at (" << targetX << ", " << targetY << ")... "<<endl;
                        r->takeDamage();
                        cout << "Remaining Shells: "<< getShells() <<endl;
                        upgrade();                        
                        break;
                    }                                    
                }
            } 
            if (!targetFound) {
                cout << "Miss no robot found at (" << targetX << ", " << targetY << ")" << endl;
                cout << "Remaining Shells: "<< getShells() <<endl;
            }          
        }else {
            cout << "Miss go cry abt it lol"<<endl;
            cout << "Remaining Shells: "<< getShells() <<endl;
        }
    }
};

