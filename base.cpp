#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "headers/ShootingRobot.h"
#include "headers/SeeingRobot.h"
#include "headers/ThinkingRobot.h"
#include "headers/MovingRobot.h"
#include "headers/GenericRobot.h"
#include "headers/Robot.h"


using namespace std;

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
    
class Battlefield{
public:
    char**a2d;
    Battlefield(vector<Robot*> &robots){
        a2d = new char*[row];
        for (int i = 0; i<row; i++) {
            a2d[i] = new char[cols];
        }

        for (int y=0; y<row; y++)
        {
            for (int x=0; x<cols; x++){ 
                a2d[y][x] = '-';
            }
        }

        for (Robot* r : robots) {
            int x = r->getX();
            int y = r->getY();

            if (x >= 0 && x < cols && y >= 0 && y < row) {
                a2d[y][x] = 'R';
            } else {
                cout << "Skipping robot at (" << x << ", " << y << ") — out of bounds\n";
            }
        }

        for (int y=0; y < row; y++){
            for(int x=0; x < cols; x++){
                cout << a2d[y][x] << " ";
            }
            cout<<endl;
            }
        }
    ~Battlefield(){
        for (int i=0;i<row;i++){
            delete[] a2d[i];
        }
        delete[] a2d;
    }
};

void parseBattlefieldGrid(string &line){
    size_t first = line.find(":")+1;
    string numbers =line.substr(first);
    stringstream ss(numbers);
    ss >> row >> cols;
    // cout << "This is m: "<< m <<" "<< "This is n: "<< n;
}

int main(){
    srand(time(0));
    vector<Robot*> robots;
    string type,namabot;
    int xcord,ycord;
    fstream myFile;
    int totalTurns = 20;
    int currentTurn = 0;


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
                robots.push_back(new GenericRobot(xcord,ycord));
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

    cout << "--- TESTING FIRE FUNCTION ---" << endl;
    
    while (currentTurn < 20) {
        cout << "\n\n======= TURN #" << currentTurn + 1 << " =======\n";

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