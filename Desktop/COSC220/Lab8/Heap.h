/*
 * Heap.h
 *
 *  Created on: Nov 11, 2020
 *      Author: kalynhowes
 */

#ifndef HEAP_H_
#define HEAP_H_

class Heap {

private:
	int arr[100];
	int size;

	int parent(int);
	int leftChild(int);
	int rightChild(int);
	void heapify(int[], int);
	void buildHeap();


public:
	Heap();
	void insert(int);
	void heapSort();
	int extractMax();
	int maximum(Heap);
	void printHeap();

};

#endif /* HEAP_H_ */


