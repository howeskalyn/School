/* Kalyn Howes
 * 4.11.21
 * Project 2
 * Linked List - header file
*/

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>
#include "Dictionary.h"

class Dictionary;

class LinkedList {

    private:

    // holds a single node of the linked list
    struct ListNode {
        ListNode *next, *prev; // doubly-linked: tracks next and previous nodes
        std::string word; // holds string
    };

    ListNode* head = nullptr; // holds the head of the LL

    friend Dictionary;

    public:
        LinkedList();
        ~LinkedList();
        void deleteNode(ListNode*);

        void putFrontNOCHECK(std::string);
        void putFront(std::string);

        ListNode* getHead() { return head; }
        int getSize();
        bool searchLocation(std::string);
        bool isEmpty();

        void printList();
        void print();
        void printAsk(Dictionary);

        LinkedList* editReplace(Dictionary, std::string);
        LinkedList* editAdd(Dictionary, std::string);
        LinkedList* editRemove(Dictionary, std::string);
        LinkedList* editSwap(Dictionary, std::string);
        int edits(Dictionary);

        LinkedList* addLLs(LinkedList*, LinkedList*, LinkedList*);
};

#endif