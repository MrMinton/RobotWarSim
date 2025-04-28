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
            // logAction --> straight away log action into output file. #parseLine
            cout << name << " moves by (" << dx << ", " << dy << ")" << endl; // #parseLine
            setPosition(getX() + dx, getY() + dy);
        }

        void fire(int dx, int dy) override {
            if (shellsRemaining > 0) {
                cout << name << " fires at (" << getX() + dx << ", " << getY() + dy << ")" << endl;  // #parseLine
                shellsRemaining--;
            } 

            if (shellsRemaining = 0) {
                cout << name << " has no shells left!" << endl; // #parseLine
                destroy();
            }
        }

        void look(int dx, int dy) override {
            cout << name << " looks at (" << getX() + dx << ", " << getY() + dy << ")" << endl;  // #parseLine
        }

        void think(vector<vector<Robot*>>& battlefield) override {
            cout << name << " is thinking..." << endl;  // #parseLine
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
        
                cout << name << " sees an enemy and fires!" << endl;
                fire(targetDX, targetDY);
            } else {
                cout << name << " finds no enemy nearby. Moving randomly." << endl;
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