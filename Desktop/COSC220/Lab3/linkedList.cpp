// Kalyn Howes
// 9.29.20
// linkedList.cpp: program file for main function and functions for managing the main function.

#include <iostream>
#include "link.h"
using namespace std;

void menu();
int validate(int);

int main() {

	node *head = NULL;

	int val = 1; // input validity check
	int m = 0; // menu selection
	while (val == 1) {
		menu();

		cin >> m;

		if (validate(m) != 0)
			val = 0;

		if (m == 1) {
			node *n = createNode();
			head = insertNode(head, n);

		} else if (m == 2) {
			int d = 0;
			cout << "\nEnter ID Number to be deleted: ";
			cin >> d;
			head = deleteNode(head, d);

		} else if (m == 3) {
			printList(head);

		} else if (m == 4) {
			int s = 0;
			cout << "\nEnter ID Number to search for: ";
			cin >> s;
			searchNode(head, s);

		} else if (m==5)
			break;
	}
	return 0;
}

// Displays a menu for the user to pick from.
void menu() {
	cout <<  endl;
	cout << "1. Insert a node\n" << "2. Delete a node\n" << "3. Print List\n"
			<< "4. Search a node – search a node and print information for a student\n"
			<< "5. Quit the program" << endl;
	cout << "Choose a menu option: ";
}

// Checks user input from menu.
int validate(int x) {

	int ret = 0;

	if (x > 5 || x < 1) {
		ret = -1;
		cout << "Invalid input, try again.";
	}

	return ret;
}
