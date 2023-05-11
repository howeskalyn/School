// Kalyn Howes
// 9.29.20
// linkFun.cpp: program file for functions for managing linked list.

#include "link.h"
#include <iostream>
using namespace std;

// Creates a node with “new” operator. Gets student data from keyboard and assigns to members of the node.
node* createNode() {
	node *newnode = new node;

	cout << "\nEnter student's last name: ";
	cin >> newnode->lastName;

	cout << "Enter student's first name: ";
	cin >> newnode->firstName;

	cout << "Enter student's ID number: ";
	cin >> newnode->idNumber;

	cout << endl;

	newnode->next = NULL;

	return newnode;
}

// Inserts a new node to the linked list sorted by student’s ID number. If the ID is already in the list, the user is told.
// Parameters: L - pointer to Linked List & N - pointer to new node
// Consider: Empty linked list, insert as a first in the list, between two nodes, last node in the list.
node* insertNode(node *L, node *N) {

	if (L == NULL)
		L = N;
	else {
		node *temp = L;
		node *behindtemp = NULL;
		while (temp->next && temp->idNumber <= N->idNumber) {
			behindtemp = temp;
			temp = temp->next;
		}
		if (N->idNumber < temp->idNumber) {
			N->next = temp;
			if (behindtemp)
				behindtemp->next = N;
			else
				L = N;
		} else
			temp->next = N;
	}
	return L;
}

// Searches a node by student ID number. The user is told if ID doesn't exist.
node* searchNode(node *L, int ID) {

	node *temp = L;
	node *returnval = NULL;
	bool found = false;

	while (temp && !found) {
		if (temp->idNumber == ID) { // if the ID is at that node
			found = true;
			returnval = temp;
		} else
			// if the ID is not at that node
			temp = temp->next;
	}

	if (found == true) {
		cout << "ID was found." << endl;
		cout << "ID Number: " << temp->idNumber << ", Name: " << temp->lastName
				<< ", " << temp->firstName << endl;
		cout << endl;
	} else
		cout << "ID was not found.\n" << endl;
	cout << endl;
	return returnval;
}

// Deletes a node from the list. The user is told if ID doesn't exist.
node* deleteNode(node *L, int ID) {

	node *delnode = searchNode(L, ID);
	node *behindtemp = NULL;
	node *temp = L;

// checks if ID is in the list
	if (delnode) {
		if (temp->idNumber == ID) { //deleting first node
			L = temp->next;
			delete temp;
		} else {
			while (temp->next) {
				behindtemp = temp;
				temp = temp->next;
				if (temp->idNumber == ID) {
					behindtemp->next = temp->next;
					temp->next = NULL;
					delete temp;
					break;
				}
			}
		}
	}
	return L;
}


// Displays all students’ information in the list. Tells user if the list is empty.
void printList(node *L) {

	node *temp = L;

	while (temp) {
		cout << "\nID Number: " << temp->idNumber << ", Name: " << temp->lastName
				<< ", " << temp->firstName << endl;
		temp = temp->next;
	}
	cout << endl;
}
