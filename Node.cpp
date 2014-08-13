/* 
 * File:   Node.cpp
 * Author: Huang xuefeng
 * 
 * Created on August 4, 2014, 4:58 PM
 */

#include "Node.h"

Node::Node(unsigned int id, unsigned int fingerTableSize) {
    fingerTable = new Node*[fingerTableSize];
    this->id = id;
}



Node::~Node() {
    delete []fingerTable;
}

unsigned int Node::getId() const{
    return id;
}

void Node::setId(unsigned int id){
    this->id = id;
}

Node** Node::getFingerTable(){
    return fingerTable;
}

vector<item>& Node::getItem(){
    return data_items;
}

