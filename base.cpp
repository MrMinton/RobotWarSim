#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "headers/Battlefield.h"
#include "headers/ShootingRobot.h"
#include "headers/SeeingRobot.h"
#include "headers/ThinkingRobot.h"
#include "headers/MovingRobot.h"
#include "headers/GenericRobot.h"
#include "headers/Robot.h"
using namespace std;

Battlefield* GenericRobot::battlefieldPtr = nullptr;

class Parse{
public:
    void parseRobots(string &line){
        size_t nombor = line.find(":")+1;
        string robots = line.substr(nombor);
        stringstream ss(robots);
        ss >> robot_amount;
        cout << "Robot amount is "<< robot_amount<<endl;
    };
};

void parseBattlefieldGrid(string &line){
    size_t first = line.find(":")+1;
    string numbers =line.substr(first);
    stringstream ss(numbers);
    ss >> row >> cols;
    // cout << "This is m: "<< m <<" "<< "This is n: "<< n;
}
void printGrid(const vector<Robot*>& robots) {
    vector<vector<string>> grid(row, vector<string>(cols, ".")); // Grid with default "."

    for (Robot* r : robots) {
        if (r->isAlive()) {
            int x = r->getX(), y = r->getY();
            if (x >= 0 && x < cols && y >= 0 && y < row) {
                grid[y][x] = string(1, toupper(r->getName()[0])); // First letter of name
            }
        }
    }

    cout << "\n🗺️ Battlefield Grid:\n";
    for (int y = 0; y < row; ++y) {
        for (int x = 0; x < cols; ++x) {
            cout << grid[y][x] << " ";
        }
        cout << endl;
    }
}


int main(){
    srand(time(0));
    vector<Robot*> robots;
    string type,namabot;
    int xcord,ycord;
    fstream myFile;
    int totalTurns = 20;
    int currentTurn = 0;

    vector<int> randomSpawnTurns;
    while (randomSpawnTurns.size() < 3) {
        int t = rand() % 10 + 1; // Random turns from 1 to 9
        if (find(randomSpawnTurns.begin(), randomSpawnTurns.end(), t) == randomSpawnTurns.end()) {
            randomSpawnTurns.push_back(t);
        }
    }


    myFile.open("gameconditions.txt", ios::in);
    if(myFile.is_open()){
        string line;
        while(getline(myFile,line)){
            if (line.find("M by N") != string::npos) {
                parseBattlefieldGrid(line);
            }
            if (line.find("robots") != string::npos){
                Parse r1;
                r1.parseRobots(line);
            }
            if(line.find("GenericRobot") != string::npos){ 
                stringstream ss(line);
                ss >> type >> namabot >> xcord >> ycord;
                if (ss.fail()){
                    xcord = rand() % cols;
                    ycord = rand() % row;
                }
                robots.push_back(new GenericRobot(namabot, xcord,ycord));
            }
        }
    }
    cout << "M: "<< row <<" "<<"N: "<< cols <<endl;
    cout << "Final dimensions -> rows: " << row << ", cols: " << cols << endl;

    for (Robot* r: robots){
        cout << r->getX() << " is x "<< r->getY() <<" is y "<<endl;
        // cout <<  r->getName();
    }

    Battlefield b1(robots);
    GenericRobot::battlefieldPtr = &b1;

    // 🚀 Force ScoutBot upgrade for testing:
    // for (Robot* r : robots) {
    //     if (GenericRobot* gr = dynamic_cast<GenericRobot*>(r)) {
    //         gr->setScoutBot(true);  // 👈 Force set it ON!
    //         cout << "✅ ScoutBot forced ON for testing!\n";
    //     }
    // }


    vector<string> namePool = {"Zeta", "Nova", "Cole"};
    
    cout << "--- TESTING FIRE FUNCTION ---" << endl;
    
    while (currentTurn < 100) {
        cout << "\n\n======= TURN #" << currentTurn + 1 << " =======\n";
        // 🆕 Spawn a GenericRobot at random turns
        if (find(randomSpawnTurns.begin(), randomSpawnTurns.end(), currentTurn + 1) != randomSpawnTurns.end()) {

            if (!namePool.empty()) {
                int randX = rand() % cols;
                int randY = rand() % row;

                int index = rand() % namePool.size();
                std::string botname = namePool[index];
                namePool.erase(namePool.begin() + index); 

                Robot* newBot = new GenericRobot(botname, randX, randY);
                robots.push_back(newBot);

                cout << "⚠️ Attention: Random GenericRobot '" << botname << "' added at (" << randX << ", " << randY << ")!\n";

                // Remove this turn so it doesn't happen again
                randomSpawnTurns.erase(remove(randomSpawnTurns.begin(), randomSpawnTurns.end(), currentTurn + 1), randomSpawnTurns.end());
            } else {
                cout << "🚫 All unique robot names used. No more robots will spawn.\n";
            }
        }

        for (Robot* r : robots) {
            if (r->isAlive()) {
                if (ThinkingRobot* thinker = dynamic_cast<ThinkingRobot*>(r)) {
                    // cout << "\n🔁 Robot at (" << r->getX() << ", " << r->getY() << ") is taking its turn...\n";ljf change this for spawn
                    thinker->think(robots);
                }
            }
        }

        cout << "\n📋 Robot Status After Turn " << currentTurn + 1 << ":\n";
        for (Robot* r : robots) {
            cout << " - Robot at (" << r->getX() << ", " << r->getY() << ") ";
            if (r->isAlive())
                cout << "is alive with " << r->getLive() << " lives and remaining shells: "<< r->getShells();
            else
                cout << "💀 DEAD";
            cout << endl;
            
        }
        printGrid(robots);
            
        
         for (Robot* r : robots) {
                r->startNewTurn();
            }

        int aliveCount = 0;
        for (Robot* r : robots) {
            if (r->isAlive()) aliveCount++;
        }

        if (aliveCount <= 1) {
            cout << "\n🏁 Game ended early: only one robot left alive.\n";
            break;
        }

        currentTurn++;
    }

    cout << "\n==============================\n";
    cout << "🏆 FINAL RESULTS:\n";
    for (Robot* r : robots) {
        cout << " - Robot at (" << r->getX() << ", " << r->getY() << ") ";
        if (r->isAlive())
            cout << "SURVIVED with " << r->getLive() << " lives and remaining shells: "<<r->getShells();
        else
            cout << "was DESTROYED.";
        cout << endl;
    }
    
    return 0;
}