/* 
 * File:   Chord.h
 * Author: Huang xuefeng
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
    void addPeer(unsigned int);
    void removePeer(unsigned int);
    void insert(unsigned int, string);
    void Delete(unsigned int, string);
    void print(unsigned int);
    ~Chord();
private:
    unsigned int size;
    unsigned int tableSize;
    set<Node*, nodeCompare> ring;
    unsigned int hash(string);
    void buildFingerTable(unsigned int);
    Node* getSuccessor(unsigned int);
    Node* getSuccessor_exclude_self(unsigned int);
    void shiftDataItem(Node*);
    Node* find(unsigned int, unsigned int);
    Node* find_helper(Node*, unsigned int);

};

#endif	/* CHORD_H */

