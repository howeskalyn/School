/* Kalyn Howes
 * 4.11.21
 * Project 2
 * Dictionary Class - header file:
 *  contains a hash table structure, with an array of pointers, to a chain 
 *  (doubly-linked list) of values and keys that each map to that cell of 
 *  the array under the chosen hash function
*/

#ifndef Dictionary_H
#define Dictionary_H

#include <iostream>
#include "LinkedList.h"

class Dictionary {

    private:
    LinkedList* T;
    int size;

    public:

    Dictionary(int); // constructor
    ~Dictionary(); // destructor

    void insert(std::string);
    size_t hash(size_t k);
    size_t strTo128(char*);

    int totalItems();
    int totalBins();
    int biggestBin();
    int smallestBin();
    int usedBins();
    double loadFactor();

    bool search(std::string);
    void printArr();
    
};

#endif