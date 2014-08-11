/* 
 * File:   Node.h
 * Author: tim
 *
 * Created on August 4, 2014, 4:58 PM
 */

#ifndef NODE_H
#define	NODE_H
#include <vector>
#include <string>
using namespace std;

class Node {
public:
    Node(unsigned int, unsigned int);
    unsigned int getId() const;
    void setId(unsigned int);
    Node** getFingerTable();
    vector<string>& getItem();
   
    ~Node();
private:
    Node** fingerTable;
    unsigned int id;
    vector<string> data_items; 
};

#endif	/* NODE_H */

