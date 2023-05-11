/*
 * Node.h - A header file for the class “Node”.
 * Kalyn Howes
 * 10.6.2020
 */

#ifndef NODE_H_
#define NODE_H_

class Node {

public:
	Node(); // Constructor
	void printNode();

	char lastName[20];
	char firstName[20];
	int idNumber;
	Node *next;

};

#endif

