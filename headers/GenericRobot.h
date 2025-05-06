#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include "MovingRobot.h"
#include "ShootingRobot.h"
#include "SeeingRobot.h"
#include "ThinkingRobot.h"
#include "Robot.h"
#include "LogAction.h"

using namespace std;

class GenericRobot : public MovingRobot, public ShootingRobot, public SeeingRobot, public ThinkingRobot {

    private:
        string name;
        int shellsRemaining;
        bool destroyed;

    public:
        GenericRobot(string robotName, int startX = 0, int startY = 0) : 
        Robot(robotName, startX, startY), MovingRobot(robotName, startX, startY), ShootingRobot(robotName, startX, startY), SeeingRobot(robotName, startX, startY), ThinkingRobot(robotName, startX, startY), name(robotName), shellsRemaining(10), destroyed(false) {}

        void move(int dx, int dy) override {            
            setPosition(getX() + dx, getY() + dy);
            cout << name << " moved to (" + to_string(getX()) + ", " + to_string(getY()) + ")";
            logAction(name + " moved to (" + to_string(getX()) + ", " + to_string(getY()) + ")");
        }

        void fire(int dx, int dy) override {
            if (shellsRemaining > 0) {
                string action = name + " fires at (" + to_string(getX() + dx) + ", " + to_string(getY() + dy) + ")";
                cout << action << endl;
                logAction(action);
                shellsRemaining--;
            } 

            if (shellsRemaining = 0) {
                string action = name + " has no shells left!";
                cout << action << endl;
                logAction(action);
                destroy();
            }
        }

        void look(int dx, int dy) override {
            string action = name + " looks at (" + to_string(getX() + dx) + ", " + to_string(getY() + dy) + ")";
            cout << action << endl;
            logAction(action);
        }

        void think(vector<vector<Robot*>>& battlefield) override {
            string action = name + " is thinking...";
            cout << action << endl;
            logAction(action);
            int currX = getX();
            int currY = getY();

            vector<pair<int, int>> enemiesAround;

            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) continue;
                    int newX = currX + dx;
                    int newY = currY + dy;
        
                    if (newX >= 0 && newX < battlefield.size() && newY >= 0 && newY < battlefield[0].size()) {
                        Robot* target = battlefield[newX][newY];
                        if (target != nullptr && target->getName() != this->name) { // If there's a robot and it's not itself
                            enemiesAround.push_back({dx, dy});
                        }
                    }
                }
            }
        
            if (!enemiesAround.empty()) {
                int idx = rand() % enemiesAround.size();
                int targetDX = enemiesAround[idx].first;
                int targetDY = enemiesAround[idx].second;
        
                string action = name + " sees an enemy and fires!";
                cout << action << endl;
                logAction(action);

                fire(targetDX, targetDY);
            } else {
                string action = name + " finds no enemy nearby. Moving randomly.";
                cout << action << endl;
                logAction(action);  
                move((rand() % 3) - 1, (rand() % 3) - 1);
            }
        }

        string getName() const {
            return name;
        }

        int getShells() const {
            return shellsRemaining;
        }

        bool isDestroyed() const {
            return destroyed;
        }

        void destroy() {
            destroyed = true;
        }
};