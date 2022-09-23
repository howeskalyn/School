/*
 * Poker.h
 *
 *  Created on: Nov 25, 2020
 *      Author: kalynhowes
 */

#ifndef POKER_H_
#define POKER_H_
#include "Card.h"

class Poker: public Card {
public:
	Poker();
	int playPoker(int);
	int handType(Card[], int);
	void sortHand(Card[]);
	int linearSearch(Card[], int);
};

#endif /* POKER_H_ */
