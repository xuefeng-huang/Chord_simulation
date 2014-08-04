/* 
 * File:   Node.h
 * Author: tim
 *
 * Created on August 4, 2014, 4:58 PM
 */

#ifndef NODE_H
#define	NODE_H

class Node {
public:
    Node(int);
   
    virtual ~Node();
private:
    int* fingerTable;
};

#endif	/* NODE_H */

