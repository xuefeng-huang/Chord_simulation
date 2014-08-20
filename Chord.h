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
    unsigned int size;//chord size
    unsigned int tableSize;//finger table size
    set<Node*, nodeCompare> ring;
    unsigned int hash(string);
    void buildFingerTable();
    Node* getSuccessor(unsigned int);
    void shiftDataItem(Node*, Node*);
    Node* find(unsigned int, unsigned int);
    Node* find_helper(Node*, unsigned int, unsigned int);

};

#endif	/* CHORD_H */

