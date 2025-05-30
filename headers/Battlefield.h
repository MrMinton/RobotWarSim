#pragma once
#include <iostream>
#include <vector>
#include "Robot.h"  // only if needed for getX(), getY(), etc.

extern int row, cols;


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
    
        void refresh(const std::vector<Robot*>& robots) {
        // Clear battlefield
        for (int y = 0; y < row; ++y)
            for (int x = 0; x < cols; ++x)
                a2d[y][x] = '-';

        // Place live robots
        for (Robot* r : robots) {
            if (r->isAlive()) {
                int x = r->getX();
                int y = r->getY();
                if (x >= 0 && x < cols && y >= 0 && y < row)
                    a2d[y][x] = 'R';
            }
        }
    }
    ~Battlefield(){
        for (int i=0;i<row;i++){
            delete[] a2d[i];
        }
        delete[] a2d;
    }
};