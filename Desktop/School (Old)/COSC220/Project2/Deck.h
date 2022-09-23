/*
 * Deck.h
 *
 *  Created on: Nov 25, 2020
 *      Author: kalynhowes
 */

#ifndef DECK_H_
#define DECK_H_
#include "Card.h"

class Deck {

public:

	vector<Card> deckOfCards; // Holds the deck of cards.
	int top; // Tracks the top of the deck.

	Deck();
	~Deck();
	void shuffleDeck();
	void printDeck();
	Card GetCard();

};

#endif /* DECK_H_ */

