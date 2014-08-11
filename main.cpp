/* 
 * File:   main.cpp
 * Author: tim
 *
 * Created on August 4, 2014, 4:23 PM
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "Chord.h"

using namespace std;

void read(char* fileName);

int main(int argc, char** argv) {
    read(argv[1]);
    
    return 0;
}

//read file instruction 
void read(char* fileName){
    ifstream input(fileName);
    
    if(input.is_open()){
        string line;
        stringstream ss;
        unsigned int num;
        bool alreadyExist = false;
        Chord* aChord = NULL;
        
        while(getline(input, line)){
            ss << line;
            ss >> line;
            
            if(line == "init"){
                if(alreadyExist){
                    delete aChord;
                    aChord = new Chord();
                    ss >> num;
                    aChord ->init(num);
                }
                else{
                    aChord = new Chord();
                    ss >> num;
                    aChord->init(num);
                    alreadyExist = true;
                }
            }
            
            ss.clear();
        }
        input.close();
    }
    else{
        cout << "cannot open file!\n";
        exit(1);
    }
}
