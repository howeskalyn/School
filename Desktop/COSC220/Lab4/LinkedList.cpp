/*
 * LinkedList.cpp - A program file for member functions of the class “LinkedList”.
 * Kalyn Howes
 * 10.6.2020
 */

#include "LinkedList.h"
#include <iostream>
using namespace std;

// Constructor - allocate a LinkedList object with list set to NULL.
LinkedList::LinkedList() {
	head = NULL;
}

// Destructor - delete all existing nodes in the List.
LinkedList::~LinkedList() {

	if (head) {
		Node *temp;
		Node *behindtemp;
		// while the head's next is not NULL
		while (head->next) {
			temp = head;
			// get to the end of the list
			while (temp->next) {
				behindtemp = temp;
				temp = temp->next;
			}
			delete temp;
			temp = NULL;
			behindtemp->next = NULL;
		}
		delete head;
		head = NULL;

	}
}

// point to the first node of a linked list
Node* LinkedList::list() {
	return head;
}

// A utility Member function which create a Node - returns pointer to created node
Node* LinkedList::createNode() {
	Node *newnode = new Node;

	cout << "\nEnter student's last name: ";
	cin >> newnode->lastName;

	cout << "Enter student's first name: ";
	cin >> newnode->firstName;

	cout << "Enter student's ID number: ";
	cin >> newnode->idNumber;

	newnode->next = NULL;

	return newnode;

}

// A utility Member function which returns a location of node for delete, insert a node in the list.
// Returns pointer to the node just before the node to search. If there is no data looking for, return NULL.
Node* LinkedList::searchLocation(int n) {
	Node *temp = head;
	Node *returnval = NULL;
	while (temp) {
		if (temp->idNumber == n) {
			returnval = temp;
			break;
		} else
			temp = temp->next;
	}

	return returnval;
}

// Insert a new node into the list. Create a Node and insert a node into right location.
// Call a private utility function “CreateNode” to create a new node, call a private utility function.
void LinkedList::insertNode() {

	Node *N = createNode();

	if (head == NULL)
		head = N;
	else {
		Node *temp = head;
		Node *behindtemp = NULL;
		while (temp->next && temp->idNumber <= N->idNumber) {
			behindtemp = temp;
			temp = temp->next;
		}
		if (N->idNumber < temp->idNumber) {
			N->next = temp;
			if (behindtemp)
				behindtemp->next = N;
			else
				head = N;
		} else
			temp->next = N;
	}

}

// Get a student ID to delete. Then, delete a specific node based on a student ID number.
/* Call a private utility function “searchLocation” to search a node to delete.
 * If there is no such a student (searchLocation returns NULL), display message “data is not available to delete in the list”
 */
void LinkedList::deleteNode(int n) {

	Node *delnode = searchLocation(n);
	Node *behindtemp = NULL;
	Node *temp = head;

// checks if ID is in the list
	if (delnode) {
		if (temp->idNumber == n) { //deleting first node
			head = temp->next;
			delete temp;
		} else {
			while (temp->next) {
				behindtemp = temp;
				temp = temp->next;
				if (temp->idNumber == n) {
					behindtemp->next = temp->next;
					temp->next = NULL;
					delete temp;
					break;
				}
			}
		}
	}

}

// Display each of student’s information in the current list.
// Call printNode() function (Node class’s public member function) to print each node with a while loop
void LinkedList::printList() {
	Node *temp = head;

	while (temp) {
		cout << "\nID Number: " << temp->idNumber << ", Name: "
				<< temp->lastName << ", " << temp->firstName << endl;
		temp = temp->next;
	}
}

// Check whether there is a student with an ID in the list.
/* Get a student ID to search and call a private utility function “searchLocation” to decide whether a
 * node is in the list or not. If there is a student with ID, print student information else (searchLocation returns NULL)
 * display a message “data is not available in the list”.
 */
void LinkedList::searchNode() {
	int n = 0;

	cout << "\nInput a student ID to search: ";
	cin >> n;

	Node *ret = searchLocation(n);

	if (ret) {
		cout << "\nID Number: " << ret->idNumber << ", Name: " << ret->lastName
				<< ", " << ret->firstName << endl;
		cout << endl;
	} else
		cout << "Data is not available in the list.\n" << endl;
}

