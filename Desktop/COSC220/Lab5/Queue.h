/*
 * Queue.h
 *
 *  Created on: Oct 20, 2020
 *      Author: kalynhowes
 */

#ifndef QUEUE_H_
#define QUEUE_H_

template<class T>
struct QueNode {

	T data;
	QueNode<T> *next;

};

template<class T>
class Queue {
private:
	QueNode<T> *front; //points to the head node
	QueNode<T> *rear; //points to the rear node, may be first if size == 0 or size == 1
	int size; //size of a Queue
	int count; // element count in a Queue

public:
	Queue(T, int = 10); //class constructor - initialize variables
	~Queue(); //class destructor – remove all memory spaces used by queue elements

	void enQueue(const T); //add an item to the back of the queue
	T* deQueue(); //remove the first item from the queue and return its value
	const T* topQueue(); //return the value of the first item in the queue
	bool isEmpty() const; //returns true if there are no elements in the queue
	bool isFull() const; //returns true if there is no system memory for a new queue node

};

#endif

