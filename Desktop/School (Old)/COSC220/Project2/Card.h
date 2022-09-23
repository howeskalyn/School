/*
 * Card.h
 *
 *  Created on: Nov 25, 2020
 *      Author: kalynhowes
 */

#ifndef CARD_H
#define CARD_H

#include <vector>
using namespace std;

class Card {

public:

	int Num = 0;
	char Pic[4];

	Card();
	~Card();
	void displayCard(int, const char[]);

	char spade[4] = "\xe2\x99\xa0";
	char club[4] = "\xe2\x99\xa3";
	char heart[4] = "\xe2\x99\xa5";
	char diamond[4] = "\xe2\x99\xa6";

};

#endif /* CARD_H_ */

