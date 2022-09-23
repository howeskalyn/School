/*
 * Card.cpp
 *
 *  Created on: Nov 25, 2020
 *      Author: kalynhowes
 */

#include "Card.h"
#include <iostream>
#include <iomanip>
using namespace std;

Card::Card() {
	Num = 0;
	for (int i = 0; i < 4; i++)
		Pic[i] = ' ';
}

Card::~Card() {

}

// Displays a card
void Card::displayCard(int num, const char pic[]) {

	cout << "---------" << endl;

	// Ace
	if (num == 1)
		cout << "|" << "A" << setw(7) << "|" << endl;
	// Jack
	else if (num == 11)
		cout << "|" << "J" << setw(7) << "|" << endl;
	// Queen
	else if (num == 12)
		cout << "|" << "Q" << setw(7) << "|" << endl;
	// King
	else if (num == 13)
		cout << "|" << "K" << setw(7) << "|" << endl;
	// a ten
	else if (num == 10)
		cout << "|" << "10" << setw(6) << "|" << endl;
	// Number card
	else
		cout << "|" << num << setw(7) << "|" << endl;

	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;

	// Ace
	if (num == 1)
		cout << "|" << "A" << setw(7) << "|" << endl;
	// Jack
	else if (num == 11)
		cout << "|" << "J" << setw(7) << "|" << endl;
	// Queen
	else if (num == 12)
		cout << "|" << "Q" << setw(7) << "|" << endl;
	// King
	else if (num == 13)
		cout << "|" << "K" << setw(7) << "|" << endl;
	// a ten
	else if (num == 10)
		cout << "|" << "10" << setw(6) << "|" << endl;
	// Number card
	else
		cout << "|" << num << setw(7) << "|" << endl;

	cout << "---------" << endl;
}


