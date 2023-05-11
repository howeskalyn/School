/*
 * Queue.cpp
 *
 *  Created on: Oct 20, 2020
 *      Author: kalynhowes
 */

#include "Queue.h"
#include <iostream>
using namespace std;

//class constructor - initialize variables
template<typename T>
Queue<T>::Queue(T i, int size) {
	front = new QueNode<T>;
	front->data = i;
	front->next = NULL;
	rear = front;
	this->size = size;
	count = 1;
}

//class destructor – remove all memory spaces used by queue elements
template<typename T>
Queue<T>::~Queue() {
	QueNode<T> *temp = front;
	QueNode<T> *behindtemp = NULL;
	if (!isEmpty()) {
		rear = NULL;
		//iterate to the end of the list
		while (temp->next) {
			behindtemp = temp;
			temp = temp->next;
		}
		delete temp;
		behindtemp->next = NULL;
	}
}

//add an item to the back of the queue
template<typename T>
void Queue<T>::enQueue(const T item) {
//check if full
	if (isFull()) {
		cout << "Queue is full." << endl;
		cout << "Try dequeuing." << endl;
	}
//the first node
	else if (isEmpty()) {
		//this is the first QueNode
		front = new QueNode<T>;
		front->data = *item;
		front->next = NULL;

		rear = front; // both point to the same locations
	} else { // neither the first item or full
		cout << "Adding item  to the back of the queue." << endl;
		QueNode<T> *newnode = new QueNode<T>;
		newnode->data = item;
		newnode->next = NULL;
		rear = newnode;
		//now actually add it to the linked list
		QueNode<T> *temp = front;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = newnode;

		count++;
	}
}
//remove the first item from the queue and return its value
template<class T>
T* Queue<T>::deQueue() {
	T *returnval = NULL;
	QueNode<T> *nextfront = NULL;
//check if empty
	if (isEmpty())
		cout << "Queue is empty, cannot remove any items." << endl;
	else {
		cout << "Removing from the front of the queue."
				<< endl;
		front = front->next;
		count--;
		*returnval = front->data;
		nextfront = front->next;
		delete front;
		front = nextfront;
	}
	return returnval;
}

//return the value of the first item in the queue
template<class T>
const T* Queue<T>::topQueue() {
	T *returnval = NULL;
	if (isEmpty())
		cout << "Queue is empty, cannot find any items." << endl;
	else
		*returnval = front->data;
	return returnval;
}

//returns true if there are no elements in the queue
template<typename T>
bool Queue<T>::isEmpty() const {
	return (count == 0);
}

//returns true if there is no system memory for a new queue node
template<typename T>
bool Queue<T>::isFull() const {
	return (count == size);
}
