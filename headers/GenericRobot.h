#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "MovingRobot.h"
#include "ShootingRobot.h"
#include "SeeingRobot.h"
#include "ThinkingRobot.h"

using namespace std;

class GenericRobot : public MovingRobot, public ShootingRobot, public SeeingRobot, public ThinkingRobot {

    private:
        string name;
        int shellsRemaining;
        bool destroyed;

    public:
        GenericRobot(string robotName, int startX = 0, int startY = 0) : Robot(startX, startY), MovingRobot(startX, startY), ShootingRobot(startX, startY), SeeingRobot(startX, startY), ThinkingRobot(startX, startY), name(robotName), shellsRemaining(10), destroyed(false) {}

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

        void think() override {
            cout << name << " is thinking..." << endl;  // #parseLine
            int currX = getX();
            int currY = getY();

            vector<
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