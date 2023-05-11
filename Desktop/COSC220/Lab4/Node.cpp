/*
 * Node.cpp - A program file for member functions of the class “Node”.
 * Kalyn Howes
 * 10.6.2020
 */

#include "Node.h"
#include <iostream>
using namespace std;

// Constructor: Member function to allocate a Node object with initialization from keyboard.
Node::Node() {

	lastName;
	firstName;
	idNumber = 0;

	next = NULL;
}

// Member function for printing a node information - ID, last name, & first name.
void Node::printNode() {
	cout << "\nID Number: " << idNumber << ", Name: " << lastName << ", "
			<< firstName << endl;
}

/* Destructor
 Node::~Node() {

 }*/

