/* 
 * File:   Chord.cpp
 * Author: Huang xuefeng
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

//add peer
void Chord::addPeer(unsigned int id){
    Node* aNode = new Node(id, tableSize);
    ring.insert(aNode);
    buildFingerTable(id);//build finger table for each node
    shiftDataItem(aNode);
}

//build finger table for each node in the ring
void Chord::buildFingerTable(unsigned int id){
    for(set<Node*>::iterator it = ring.begin(); it != ring.end(); it++){
        unsigned int id_in_ring = (*it)->getId();
        
        for(unsigned int i = 0; i < tableSize; i++){
            unsigned int interval = (1 << i);
            unsigned int mapped_id = (id_in_ring + interval) & (size - 1); //successor number mod size of the ring
            if(id_in_ring < id && mapped_id <= id || id_in_ring >= id){
                (*it)->getFingerTable()[i] = getSuccessor(mapped_id);
            }
        }
    }
}

//return successor pointer of a given id
Node* Chord::getSuccessor(unsigned int id){
    for(set<Node*>::iterator it = ring.begin(); it != ring.end(); it++){
        if((*it)->getId() >= id)
            return (*it);
    }
    //no bigger id found, return pointer of first node
    return *(ring.begin());
}

//return pointer of next successor not include self
Node* Chord::getSuccessor_exclude_self(unsigned int id){
    for(set<Node*>::iterator it = ring.begin(); it != ring.end(); it++){
        if((*it)->getId() > id)
            return (*it);
    }
    //no bigger id found, return pointer of first node
    return *(ring.begin());
}

//shift data item from successor to newly added node
void Chord::shiftDataItem(Node* node){
    Node* successor = getSuccessor(node->getId());
    vector<item> successor_item = successor->getItem();
    unsigned int successor_id = successor->getId();
    
    vector<item>::iterator it = successor_item.begin();
    while(it != successor_item.end()){
        if((*it).key != successor_id && (*it).key <= node->getId()){
            (node->getItem()).push_back((*it));
            it = successor_item.erase(it);
        }
        else
            it++;
    }
}

//remove a peer of id
void Chord::removePeer(unsigned int id){
    set<Node*>::iterator it = ring.begin();
    
    if(ring.size() == 1 && (*it)->getId() == id){
        delete (*it);
        ring.erase(it);
        cout << "peer " << id << " removed. This is last peer, chord is now empty\n"; 
    }
    else{
        Node* successor = getSuccessor(id);
        while(it != ring.end()){
            if((*it)->getId() == id){
                vector<item> data = (*it)->getItem();
                for(vector<item>::iterator itr = data.begin(); itr != data.end(); itr++){
                    successor->getItem().push_back((*itr));//push all item to successor
                }
                delete (*it);
                ring.erase(it);
                break;
            }
            it++;
        }
        buildFingerTable(id);//rebuild finger table after remove peer
        cout << "peer " << id << " removed\n";
    }
    
}

//insert a string
void Chord::insert(unsigned int id, string data){
    unsigned int position = hash(data);
    cout << "inserting " << data << " at " << position << endl;
    Node* final_position = find(id, position);
    //insert item into peer
    item anItem;
    anItem.key = position;
    anItem.value = data;
    final_position->getItem().push_back(anItem);
}

//find a peer start from id and return a successor if not found
Node* Chord::find(unsigned int id, unsigned int position){
    Node* final_node = NULL;
    
    for(set<Node*>::iterator it = ring.begin(); it != ring.end(); it++){
        if((*it)->getId() == id){
            if(id == position){//start peer and hash code is the same
                cout << id << endl;
                return (*it);
            }
            cout << id << " > ";
            final_node = find_helper((*it), position);
            break;
        }
    }
    return final_node;
    
    
}

//return the peer node responsible for the searching position
Node* Chord::find_helper(Node* start_node, unsigned int position){
    Node** table = start_node->getFingerTable();
    Node* successor = getSuccessor_exclude_self(start_node->getId());
    Node* searching_node_successor = getSuccessor(position);
   
    if(successor->getId() == searching_node_successor->getId()){//between this peer and successor
        cout << successor->getId() << endl;
        return successor;
    }
    
    Node* nearest_node = table[0];
    unsigned int difference = position - table[0]->getId();
    
    for(unsigned int i = 1; i < tableSize; i++){
        if(table[i]->getId() == position){
            cout << table[i]->getId() << endl;
            return table[i];
        }
        else{
            if(table[i]->getId() < position && (position - table[i]->getId()) < difference){
                nearest_node = table[i];
                difference = position - table[i]->getId();
            }
        }
    }
    cout << nearest_node->getId() << " > ";
    //call helper recursively to find the peer
    find_helper(nearest_node, position);
    
}

void Chord::Delete(unsigned int id, string data){
    unsigned int position = hash(data);
    Node* final_position = find(id, position);
    vector<item> items = final_position->getItem();
    
    for(vector<item>::iterator it = items.begin(); it != items.end(); it++){
        if((*it).value == data){
            items.erase(it);
            break;
        }
    }
    cout << "deleted " << data << " from " << final_position->getId() << endl;
}

void Chord::print(unsigned int position){
    Node* final_node = find(0, position);//start searching from node 0
    unsigned int id = final_node->getId();
    vector<item> items = final_node->getItem();
    Node** table = final_node->getFingerTable();
    
    cout << "data at index node: " << id << " :\n";
    for(vector<item>::iterator it = items.begin(); it != items.end(); it++){
        cout << (*it).value << endl;
    }
    
    cout << "finger table of index node: " << id << " :\n";
    for(int i = 0; i < tableSize; i++){
        cout << table[i]->getId() << " ";
    }
    cout << endl;
}
