/*
 * LinkedList.h - A header file for the class “LinkdedList”.
 * Kalyn Howes
 * 10.6.2020
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "Node.h"

class LinkedList {

private:
	Node *list();
	Node *createNode();
	Node *searchLocation(int);
	Node *head;
	// int NodeCount;

public:
	LinkedList(); // Constructor
	~LinkedList(); // Destructor

	void insertNode();
	void deleteNode(int);
	void printList();
	void searchNode();

};

#endif

