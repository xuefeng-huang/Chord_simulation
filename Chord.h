/* 
 * File:   Chord.h
 * Author: tim
 *
 * Created on August 4, 2014, 5:32 PM
 */

#ifndef CHORD_H
#define	CHORD_H
#include <string>
#include <set>
#include "Node.h"
using namespace std;

struct nodeCompare{
    bool operator()(const Node* a, const Node* b){
        return a->getId() < b->getId();
    }
};

class Chord {
public:
    Chord();
    void init(unsigned int);
    ~Chord();
private:
    unsigned int size;
    unsigned int tableSize;
    set<Node*, nodeCompare> ring;
    unsigned int hash(string);

};

#endif	/* CHORD_H */

