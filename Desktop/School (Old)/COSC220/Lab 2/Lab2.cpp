// Kalyn Howes
// 9/22/20

#include <iostream>
#include <fstream>
#include <vector>
#include<stdio.h>
using namespace std;

// Struct to hold each grocery item info:
struct Item {
	char tax, type;
	char name[100];
	int number;
	double price;
};

int main() {

	// Opening files & error checking:
	ifstream inputFile;
	ofstream outputFile;
	inputFile.open("item.txt");
	outputFile.open("Howes_Kalyn.txt");

	if (!inputFile)
		cerr << "Input file could not open.";
	if (!outputFile)
		cerr << "Output file could not open.";

	// Output file set up:
	outputFile
			<< "Item number    Item Name       Unit     Unit price      Tax       Subtotal"
			<< endl;
	outputFile
			<< "-----------    ---------       ----     ----------      ---       --------"
			<< endl;

	// Insert file data into a vector of structs
	vector<Item> G;
	while (inputFile) {
		Item i;
		inputFile >> i.number;
		inputFile >> i.name;
		inputFile >> i.tax;
		inputFile >> i.type;
		inputFile >> i.price;

		G.push_back(i);
	}

	// Variable set up
	int itemNum = 1;
	int x = 0; // match when found
	double subtotal = 0;
	double total = 0;

	// User input until 0:
	while (itemNum != 0) {

		cout << "Input an item number: ";
		cin >> itemNum;

		// If user input in 0, quit
		if (itemNum != 0) {

			// Item number check:
			for (int i = 0; i < G.size(); i++) {
				if (itemNum == G[i].number) {
					x = i;
					break;
				} else
					x = -1;
			}
			if (x == -1)
				cout << "Invalid item number, try again.\n" << endl;
			else {
				// Unit type check:
				double lb = 0;
				int u = 0;
				if (G[x].type == 'p') {
					cout << "Input number of pounds: ";
					cin >> lb;
					subtotal = lb * G[x].price;

					// Taxable check:
					double t = 0;
					if (G[x].tax == 't') {
						t = subtotal * 0.06;
						subtotal = subtotal + t;
					}
					setw(5);
					setprecision(2);
					outputFile << G[x].number << "        " << G[x].name << "    " << lb
												<< "      " << G[x].price << "       " << t << "       " << subtotal
												<< "\n" << endl;

				} else if (G[x].type == 's') {
					cout << "Input number of units: ";
					cin >> u;
					subtotal = u * G[x].price;

					// Taxable check:
					double t = 0;
					if (G[x].tax == 't') {
						t = subtotal * 0.06;
						subtotal = subtotal + t;
					}
					setw(5);
					setprecision(2);
					outputFile << G[x].number << "        " << G[x].name << "    " << u
							<< "      " << G[x].price << "       " << t << "       " << subtotal
							<< "\n" << endl;

				} else {
					// Taxable check:
					double t = 0;
					if (G[x].tax == 't') {
						t = subtotal * 0.06;
						subtotal = subtotal + t;
					} else
						subtotal = G[x].price;
				}

			}
			total += subtotal;
		}

	}

	outputFile
			<< "Total                                                        "
			<< total << endl;

	// Close all files:
	inputFile.close();
	outputFile.close();

	return 0;
}
