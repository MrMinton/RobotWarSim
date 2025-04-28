#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


int m,n;

class Battlefield{
public:
    char**a2d;

    Battlefield(){
        a2d = new char*[m];
        for (int i = 0; i<m; i++) {
            a2d[i] = new char[n];
        }

        for (int y=0; y<m; y++)
        {
            for (int x=0; x<n; x++){
                a2d[y][x] = '-';
            }
        }

        for (int y=0; y < m; y++){
            for(int x=0; x < n; x++){
                cout << a2d[y][x];
            }
            cout<<endl;
            }
        }

    ~Battlefield(){
        for (int i=0;i<m;i++){
            delete[] a2d[i];
        }
        delete[] a2d;
    }

    
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
    Battlefield b1;
    return 0;
}