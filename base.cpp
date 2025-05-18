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
        int x, y;
    public:
        Robot(){};
        Robot(int x_coord,int y_coord){
            x = x_coord;
            y = y_coord;
        }
        int getX(){
            return x;
        }
    
        int getY(){
            return y;
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
    Battlefield(vector<Robot> &robots){
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

        for (Robot r : robots) {
            int x = r.getX();
            int y = r.getY();

            if (x >= 0 && x < cols && y >= 0 && y < row) {
                a2d[y][x] = 'R';
            } else {
                cout << "❗ Skipping robot at (" << x << ", " << y << ") — out of bounds\n";
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
    vector<Robot> robots;
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
                    srand(time(0));
                    xcord = rand() % cols;
                    ycord = rand() % row;
                }
                Robot bot(xcord,ycord);
                robots.push_back(bot);
            }
        }
    }
    cout << "M: "<< row <<" "<<"N: "<< cols <<endl;
    cout << "Final dimensions -> rows: " << row << ", cols: " << cols << endl;

    for (Robot r: robots){
        cout << r.getX() << " is x "<< r.getY() <<" is y "<<endl;
    }
    Battlefield b1(robots);
    return 0;
}