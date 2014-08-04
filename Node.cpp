/* 
 * File:   Node.cpp
 * Author: tim
 * 
 * Created on August 4, 2014, 4:58 PM
 */

#include "Node.h"

Node::Node(int fingerTableSize) {
    fingerTable = new int[fingerTableSize];
}



Node::~Node() {
}

