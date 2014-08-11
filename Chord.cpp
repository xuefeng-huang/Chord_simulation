/* 
 * File:   Chord.cpp
 * Author: tim
 * 
 * Created on August 4, 2014, 5:32 PM
 */

#include "Chord.h"
#include <iostream>

Chord::Chord() {
}



Chord::~Chord() {
    for(set<Node*>::iterator it = ring.begin(); it != ring.end(); it++){
        delete *it;
    }
}

unsigned int Chord::hash(string data){
    unsigned int key = 0;
    for(string::iterator it = data.begin(); it != data.end(); it++){
        key = ((key << 5) + key) ^ *it;
    }
    /*size is in power of 2, just return the part from key which is not multiple of size
     * faster than normal mod operator. more info on:
     * http://graphics.stanford.edu/~seander/bithacks.html#ModulusDivisionEasy*****/
    return key & (size - 1);
}

//init chord
void Chord::init(unsigned int size){
    cout << "Huang xuefeng\n" << "4403290\n";
    
    this->size = size;
    //compute finger table size
    tableSize = 0;
    while(size >>= 1)
        tableSize++;
    
    //create node 0
    Node* nodeZero = new Node(0, tableSize);
    ring.insert(nodeZero);
    //fill in finger table pointer
    for(unsigned int i = 0; i < tableSize; i++){
        nodeZero->getFingerTable()[i] = nodeZero;
    }
}

