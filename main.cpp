/* 
 * File:   main.cpp
 * Author: Huang xuefeng
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
            ss >> line;//read first word for command
            
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
            else if(line == "addpeer"){
                ss >> num;
                aChord->addPeer(num);
                cout << "peer id " << num << " inserted\n";
            }
            else if(line == "removepeer"){
                ss >> num;
                aChord->removePeer(num);
            }
            else if(line == "insert"){
                ss >> num;
                getline(ss, line);
                aChord->insert(num, line);
            }
            else if(line == "delete"){
                ss >> num;
                getline(ss, line);
                aChord->Delete(num, line);
            }
            else if(line == "print"){
                ss >> num;
                aChord->print(num);
            }
            
            ss.clear();
            ss.str("");//clear stream buffer if command is not in one of the above
        }
        input.close();
    }
    else{
        cout << "cannot open file!\n";
        exit(1);
    }
}
