//============================================================================
// Name        : Lab7.cpp
// Author      : Kalyn Howes
// Date        : 11.10.2020
// Description : Binary Search Tree
//============================================================================

#include <iostream>
#include "TNode.h"
#include "BST.h"

using namespace std;

int printmenu();

int main() {

	// Create tree
	BST tree;

	// Establish some variables
	int choice = 0;
	int data = 0;

	// Until user quits...
	while (choice != 6) {
		choice = printmenu();

		if (choice == 1) {
			cout << "\nInput data to be inserted: ";
			cin >> data;
			tree.bstInsert(data);
			cout << endl;

		} else if (choice == 2) {
			cout << "\nInput data to be deleted: ";
			cin >> data;
			tree.bstDelete(data);
			cout << endl;

		} else if (choice == 3) {
			cout << "\nDisplaying tree in preorder." << endl;
			tree.preOrder(tree.GetRoot());
			cout << endl;

		} else if (choice == 4) {
			cout << "\nDisplaying tree inorder." << endl;
			tree.inOrder(tree.GetRoot());
			cout << endl;

		} else if (choice == 5) {
			cout << "\nDisplaying tree in postorder." << endl;
			tree.postOrder(tree.GetRoot());
			cout << endl;
		}

	}

	cout << "Qutting the program." << endl;

	return 0;
}

// prints menu and returns chosen number - checks for valid input
int printmenu() {
	int n = 0;
	bool validate = true;

	while (validate) {
		cout << "----MENU----" << endl;
		cout << "1: Inserts a new element." << endl;
		cout << "2: Removes an element." << endl;
		cout << "3: Print Preorder." << endl;
		cout << "4: Print Inorder." << endl;
		cout << "5: Print Postorder." << endl;
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
