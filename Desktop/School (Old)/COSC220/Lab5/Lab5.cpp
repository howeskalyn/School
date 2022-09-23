#include "Queue.h"
#include "Students.h"
using namespace std;

int printmenu();

int main() {
	Queue<Students> *squeue = NULL; //a queue with Student data type
	//Queue<int> *iqueue = NULL; // a queue with integer data type

	int choice = 0;

	while (choice != 4) {
		choice = printmenu();
		if (choice == 1) {
			Students s;
			squeue->enQueue(s);
		} else if (choice == 2) {
			Students ret;
			squeue->deQueue();
			cout << "Removed first item from the queue." << endl;
		} else if (choice == 3) {
			Students const *ret = squeue->topQueue();
			cout << "First item in the queue is: " << ret << endl;
		}
	}

	cout << "Quitting the program..." << endl;

	return 0;
}

// prints menu and returns chosen number - checks for valid input
int printmenu() {
	int n = 0;
	bool validate = true;

	while (validate) {
		cout << "----MENU----" << endl;
		cout << "1: enQueue - inserts a new element at the end of the Queue."
				<< endl;
		cout << "2: deQueue - removes an element from the front of the Queue."
				<< endl;
		cout << "3: topQueue - displays data from the top of Queue." << endl;
		cout << "4: quit - quits program." << endl;
		cout << "Enter your choice number: ";
		cin >> n;

		if (n < 0 || n > 4) {
			validate = true;
			cout << "\nInvalid menu input. Try again." << endl;
		} else
			validate = false;
	}
	return n;
}

