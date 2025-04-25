#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


int m,n;

class Battlefield{
public:
    int grid[m][n]; //ini belum settle buat yg lain dulu
};



void parseBattlefieldGrid(string &line){
    size_t first = line.find(":")+1;
    string numbers =line.substr(first);
    stringstream ss(numbers);
    ss >> m >>n;
    // cout << "This is m: "<< m <<" "<< "This is n: "<< n;
}

int main(){
    fstream myFile;
    myFile.open("gameconditions.txt", ios::in);
    if(myFile.is_open()){
        string line;
        while(getline(myFile,line)){
            if (line.find("M by N") != string::npos) {
                parseBattlefieldGrid(line);
            }
        }
    }
    cout << "M: "<<m <<" "<<"N: "<<n <<endl;
    return 0;
}