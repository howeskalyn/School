/*
 * Deck.cpp
 *
 *  Created on: Nov 25, 2020
 *      Author: kalynhowes
 */

#include "Deck.h"
#include "Card.h"
#include <iostream>
using namespace std;

Deck::Deck() {
	top = 0;

	// for each of the 4 suits
	for (int suit = 0; suit < 4; suit++) {

		// for each of the 13 different values in each suit
		for (int number = 0; number < 13; number++) {
			Card temp;
			temp.Num = number + 1; 	// Ace is 1, 2 is 2 ... J is 11, Q is 12, K is 13

			switch (suit) {

			case 0: // make a spade card
				for (int i = 0; i < 4; i++) {
					temp.Pic[i] = temp.spade[i];
				}
				break;

			case 1: // make a club card
				for (int i = 0; i < 4; i++) {
					temp.Pic[i] = temp.club[i];
				}
				break;

			case 2:  // make a heart card
				for (int i = 0; i < 4; i++) {
					temp.Pic[i] = temp.heart[i];
				}
				break;

			case 3:  // make a diamond card
				for (int i = 0; i < 4; i++) {
					temp.Pic[i] = temp.diamond[i];
				}
				break;
			}
			// cout << "adding " << temp.num << " of " << temp.pic << endl;

			// add the card to the deck
			deckOfCards.push_back(temp);
		}
	}
}

Deck::~Deck() {

}

// shuffle deck
void Deck::shuffleDeck() {
	srand(time(0));
	srand((unsigned) time( NULL));

	int k;
	Card temp;

	for (int i = 0; i < 52; i++) {
		k = i + (rand() % (52 - i));
		temp = deckOfCards[i];
		deckOfCards[i] = deckOfCards[k];
		deckOfCards[k] = temp;
	}

	//NextCard = 0;

}

// Prints the whole deck
void Deck::printDeck() {

	for (int i = 0; i < 52; i++) {
		cout << "------" << endl;
		cout << deckOfCards[i].Num << endl;
		cout << deckOfCards[i].Pic << endl;
		cout << "------" << endl;
	}
}

// Returns next card
Card Deck::GetCard() {
	return deckOfCards[top++];
}


