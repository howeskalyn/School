//============================================================================
// Name        : Lab8.cpp
// Author      : Kalyn Howes
// Date        : 11.24.2020
// Description : Heap implementation.
//============================================================================

#include <iostream>
#include "Heap.h"
using namespace std;

int printmenu();

int main() {

	// Creates heap
	Heap H;

	// Establish some variables
	int choice = 0;
	int n = 0;

	// Until user quits...
	while (choice != 6) {
		choice = printmenu();

		if (choice == 1) {
			cout << "\nInput element to be inserted: ";
			cin >> n;
			H.insert(n);
			cout << endl;

		} else if (choice == 2) {
			int max = H.maximum(H);
			cout << "\nMax is: " << max << endl;
			cout << endl;

		} else if (choice == 3) {
			H.extractMax();
			cout << endl;

		} else if (choice == 4) {
			H.printHeap();
			cout << endl;

		} else if (choice == 5) {
			H.heapSort();
			cout << endl;
		}

	}

	cout << "\nQutting the program." << endl;

	return 0;
}

// prints menu and returns chosen number - checks for valid input
int printmenu() {
	int n = 0;
	bool validate = true;

	while (validate) {
		cout << "----MENU----" << endl;
		cout << "1: Inserts a new element." << endl;
		cout << "2: Finds maximum element." << endl;
		cout << "3: Extracts maximum element." << endl;
		cout << "4: Prints the heap." << endl;
		cout << "5: Sorts the heap (& prints results)." << endl;
		cout << "6: Quit program." << endl;
		cout << "Enter your choice number: ";
		cin >> n;

		if (n < 0 || n > 7) {
			validate = true;
			cout << "\nInvalid menu input. Try again." << endl;
		} else
			validate = false;
	}
	return n;
}

