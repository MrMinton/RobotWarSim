#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "headers/Robot.h"
#include "headers/GenericRobot.h"
#include "headers/LogAction.h"


using namespace std;


int row = 50,cols = 50;

void writeGameConditions(int rows, int cols, int steps, const vector<GenericRobot*>& robots) {
    ofstream outFile("gameconditions.txt");
    if (!outFile.is_open()) {
        cerr << "Failed to open gameconditions.txt\n";
        return;
    }

    outFile << "M by N : " << rows << " " << cols << "\n";
    outFile << "steps: " << steps << "\n";
    outFile << "robots: " << robots.size() << "\n";

    for (const auto& robot : robots) {
        if (robot) {
            outFile << "GenericRobot " << robot->getName() << " " << robot->getX() << " " << robot->getY() << "\n";
        }
    }

    outFile.close();
}

void logAction(const string& message) {
    static ofstream actionLog("actionlog.txt", ios::app);
    if (!actionLog.is_open()) {
        cerr << "Failed to open gameconditions.txt\n";
        return;
    }

    actionLog << message << endl;
}
// int robot_amount;

// class Robot{
//     private:
//         int x, y;
//     public:
//         Robot(){};
//         Robot(int x_coord,int y_coord){
//             x = x_coord;
//             y = y_coord;
//         }
//         int getX(){
//             return x;
//         }
    
//         int getY(){
//             return y;
//         }
//         void parseRobots(string &line);
//     };
    
//     void Robot::parseRobots(string &line){
//         size_t nombor = line.find(":")+1;
//         string robots = line.substr(nombor);
//         stringstream ss(robots);
//         ss >> robot_amount;
//         cout << "Robot amount is "<< robot_amount<<endl;
//     }
    
// class Battlefield{
// public:
//     char**a2d;
//     Battlefield(vector<Robot> &robots){
//         a2d = new char*[row];
//         for (int i = 0; i<row; i++) {
//             a2d[i] = new char[cols];
//         }

//         for (int y=0; y<row; y++)
//         {
//             for (int x=0; x<cols; x++){ 
//                 a2d[y][x] = '-';
//             }
//         }

//         for (Robot r: robots){
//             a2d[r.getY()][r.getX()] = 'R';
//         }
        
//         for (int y=0; y < row; y++){
//             for(int x=0; x < cols; x++){
//                 cout << a2d[y][x] << " ";
//             }
//             cout<<endl;
//             }
//         }

//     ~Battlefield(){
//         for (int i=0;i<row;i++){
//             delete[] a2d[i];
//         }
//         delete[] a2d;
//     }

    
// };

void parseBattlefieldGrid(string &line){
    size_t first = line.find(":")+1;
    string numbers =line.substr(first);
    stringstream ss(numbers);
    ss >> cols >> row;
    // cout << "This is m: "<< m <<" "<< "This is n: "<< n;
}

int main(){
    vector<GenericRobot*> robots;

    ofstream logAction("actionlog.txt");

    robots.push_back(new GenericRobot("Patrick", 2, 3));
    robots.push_back(new GenericRobot("Kai", 5, 4));

    writeGameConditions(row, cols, 50, robots);

    for (GenericRobot* robot : robots) {
        delete robot;
    }

    logAction.close();

    return 0;
}