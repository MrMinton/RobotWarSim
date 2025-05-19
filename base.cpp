#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;


int row,cols;
int robot_amount;

class Robot{
private:
    bool alive = true;
    string name;
    string type;
    int x, y;
    int lives =3;
    int shells =10;

public:
    Robot(){};
    Robot(int x_coord,int y_coord){
        x = x_coord;
        y = y_coord;
    }
    virtual ~Robot();
    int getX(){
        return x;
    }
    
    int getY(){
        return y;
    }

    int getShells(){
        return shells;
    }

    bool isAlive(){
        return alive;
    }

    void selfDestruct(){
        alive = false;
        lives--;
    }
    void takeDamage() {
        lives--;
        if (lives <= 0) {
            alive = false;
            cout << "Robot " << name << " has been destroyed!" << endl;
        } else {
            cout << "Robot " << name << " was hit! Lives left: " << lives << endl;
        }
    }

    int getLive(){
        return lives;
    }
    virtual void think()=0;
    virtual void move()=0;
    virtual void look()=0;
    virtual void fire(vector<Robot*>& robots) = 0;

    };

Robot::~Robot() {}


class GenericRobot : public Robot{
public:
    GenericRobot(int x_coord, int y_coord):Robot(x_coord,y_coord){};
    void think(){};
    void move() {};
    void look() {};

    void fire(vector<Robot*>& robots) {
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

        if (targetX < 0 || targetX >= cols || targetY < 0 || targetY>=row){
            cout << "Out of bounds"<< endl;
        }

        int hitprob = rand() % 100;
        
        if (hitprob < 70){
            cout << "Hit"<<endl;
            for (Robot* r : robots) {
                if (r->isAlive() && r->getX() == targetX && r->getY() == targetY) {
                    r->takeDamage();
                    break;
                    }
                }
            }
        else {
            cout << "Miss"<<endl;
        }
    }
};

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
    }

    Battlefield b1(robots);

    cout << "\n--- TESTING FIRE FUNCTION ---" << endl;

    if (!robots.empty()) {
        cout << "Robot at (" << robots[0]->getX() << ", " << robots[0]->getY() << ") is firing...\n";
        robots[0]->fire(robots);
    }
    for (Robot* r: robots){
        cout << r->getLive()<<endl;
    }

    return 0;
}