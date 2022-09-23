/*
 * Heap.cpp
 *
 *  Created on: Nov 11, 2020
 *      Author: kalynhowes
 */

#include "Heap.h"
#include <iostream>

// Constructor - initiates array with {4, 12, 3, 19, 23, 5, 32, 11, 2, 24}
// Sets size to 10 and calls BuildHeap function to build a heap
Heap::Heap() {
	size = 10;

	int arr2[] = { 4, 12, 3, 19, 23, 5, 32, 11, 2, 24 };

	for (int i = 0; i < size; i++) {
		arr[i] = arr2[i];
	}

	buildHeap();
}

// Returns index of parent of i
int Heap::parent(int i) {

	int ret = 0;

	//if i is 0, it cannot have a parent
	if (i == 0)
		ret = 0;
	//if i is even
	else if (i % 2 == 0)
		ret = (i - 1) / 2;
	// if i is odd
	else
		ret = (i / 2);

	return ret;
}

// Returns index of left child of i
int Heap::leftChild(int i) {
	return (2 * i + 1);
}

// Returns index of right child of i
int Heap::rightChild(int i) {
	return (2 * i + 2);
}

// Heapify
void Heap::heapify(int arr[], int i) {

	int largest = i; // initialize largest as root
	int l = 2 * i + 1; // left = 2*i + 1
	int r = 2 * i + 2; // right = 2*i + 2

	// if left child is larger than root
	if (l < size && arr[l] > arr[largest])
		largest = l;

	// if right child is larger than largest so far
	if (r < size && arr[r] > arr[largest])
		largest = r;

	// if largest is not root
	if (largest != i) {
		int temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;

		// recursively heapify the affected sub-tree
		heapify(arr, largest);
	}

}

// Builds a Heap
void Heap::buildHeap() {

	// index of last non-leaf node
	int start = (size / 2) - 1;

	// reverse level order traversal from last non-leaf node - heapify each node
	for (int i = start; i >= 0; i--) {
		heapify(arr, i);
	}

}

// Inserts new data into the Heap
void Heap::insert(int key) {

	int i = size;
	size = size + 1;

	while (i > 0 && arr[parent(i)] < key) {
		arr[i] = arr[parent(i)];
		i = parent(i);
	}

	arr[i] = key; //copy the key value in the right location

}

// Sorts the Heap
void Heap::heapSort() {

	int j, min, temp = 0;
	for (int i = 0; i < size - 1; i++) {
		min = i;
		for (j = i + 1; j < size; j++)
			if (arr[j] < arr[min])
				min = j;
		temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;

	}
	printHeap();

}

// Extracts maximum value from the Heap & deletes it
int Heap::extractMax() {

	int max = arr[0];

	if (size < 1)
		std::cout << "Error: Heap underflow." << std::endl;
	else {
		for (int i = 1; i < size; i++)
			if (arr[i] > max)
				max = arr[i];
	}
	// Deleting the max:
	size = size - 1;
	heapSort();
	for (int j = max; j < size; j--)
		arr[j] = arr[j + 1];
	std::cout << "\n";
	std::cout << max << " has been deleted." << std::endl;

	return max;
}

// Returns maximum value in the Heap
int Heap::maximum(Heap A) {

	int max = A.arr[0];

	if (size < 1)
		std::cout << "Error: Heap underflow." << std::endl;
	else {
		for (int i = 1; i < size; i++)
			if (A.arr[i] > max)
				max = A.arr[i];
	}

	return max;
}

// Prints the Heap in leveled form
void Heap::printHeap() {

	int level = 0; // zero is the top most level
	int n = 1; // number of items at level
	int p = 0; // number of items printed at this level

	// for each item in the heap
	for (int i = 0; i < size; i++) {
		if (p == 0) { // start of a new level
			std::cout << "\nLevel " << level << ": ";
		}

		std::cout << arr[i] << ' ';
		++p;

		// completed this level
		if (p == n) {
			++level;
			n *= 2; // next level has at most twice as many items
			p = 0;
		}
	}

	std::cout << '\n';
}

