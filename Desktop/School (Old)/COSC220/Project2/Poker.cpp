/*
 * Poker.cpp
 *
 *  Created on: Nov 25, 2020
 *      Author: kalynhowes
 */

#include "Poker.h"
#include "Card.h"
#include "Deck.h"
#include <iostream>
#include <cstring> // for strcmp
using namespace std;

Poker::Poker() {
}

// takes in bet amount & returns amount of winnings
int Poker::playPoker(int bet) {

	Deck D;
	D.shuffleDeck();

	// Create Hand storage
	Card Hand[5];
	Card C;

	// fill Hand with 5 cards
	for (int i = 0; i < 5; i++) {
		Hand[i] = (D.GetCard());
	}

	/* TESTING HAND TYPES:
	 Hand[0].Num = 3;
	 Hand[1].Num = 2;
	 Hand[2].Num = 5;
	 Hand[3].Num = 4;
	 Hand[4].Num = 6;
	 for (int j = 0; j < 5; j++) {
	 for (int i = 0; i < 4; i++) {
	 Hand[j].Pic[i] = Hand[j].spade[i];
	 }
	 }
	 /*
	 for (int i = 0; i < 4; i++) {
	 Hand[1].Pic[i] = Hand[1].heart[i];
	 }
	 for (int i = 0; i < 4; i++) {
	 Hand[2].Pic[i] = Hand[2].spade[i];
	 }
	 for (int i = 0; i < 4; i++) {
	 Hand[3].Pic[i] = Hand[3].diamond[i];
	 }
	 for (int i = 0; i < 4; i++) {
	 Hand[4].Pic[i] = Hand[4].club[i];
	 }*/

	// display all 5 cards
	cout << "Your Hand: " << endl;
	for (int i = 0; i < 5; i++) {
		C.displayCard(Hand[i].Num, Hand[i].Pic);
	}

	// hold or redraw cards?
	int n = 0;
	for (int i = 0; i < 5; i++) {
		cout << "Your " << i + 1 << " card: " << endl;
		C.displayCard(Hand[i].Num, Hand[i].Pic);
		cout << "Do you wish to Hold (1) or Redraw(0) this card? ";
		cin >> n;
		// if redrawn replace old card with drawn new card
		if (n == 0) {
			Hand[i] = D.GetCard();
		}
	}

	// sorts hand
	sortHand(Hand);

	// Print final 5 cards
	cout << "Final 5 Cards:" << endl;
	for (int i = 0; i < 5; i++)
		C.displayCard(Hand[i].Num, Hand[i].Pic);

	int winnings = handType(Hand, bet);

	return winnings;
}

// Sorts Hand
void Poker::sortHand(Card H[]) {
	int size = 5;
	Card c, c2; // Hold two cards.
	int maxElement = 0, index = 0; // Holds the maximum element and the index.
	// Goes through until the maximum element becomes 0.
	for (maxElement = size - 1; maxElement > 0; maxElement--)
		// Goes through while the index is smaller than the maximum element.
		for (index = 0; index < maxElement; index++) {
			c = H[index];
			c2 = H[index + 1];
			// If the Card 1 value is larger than the Card 2 value, they are swapped.
			if (c.Num > c2.Num) {
				Card temp = H[index];
				H[index] = H[index + 1];
				H[index + 1] = temp;
			}
		}
}

// finds the type of hand the player has and returns the amount they won
int Poker::handType(Card H[], int bet) {
	int money = 0;

	// Royal Straight Flush:
	if ((strcmp(H[0].Pic, H[1].Pic) == 0 && strcmp(H[1].Pic, H[2].Pic) == 0
			&& strcmp(H[2].Pic, H[3].Pic) == 0
			&& strcmp(H[3].Pic, H[4].Pic) == 0)
			&& (H[0].Num == 1 && H[1].Num == 10 && H[2].Num == 11
					&& H[3].Num == 12 && H[4].Num == 13)) {
		// & you have a A, K, Q, J, 10
		cout << "You have a Royal Straight Flush!" << endl;
		money = bet * 10000;

		// Straight Flush:
	} else if ((H[1].Num == H[0].Num + 1 && H[2].Num == H[1].Num + 1
			&& H[3].Num == H[2].Num + 1 && H[4].Num == H[3].Num + 1)
			&& (strcmp(H[0].Pic, H[1].Pic) == 0
					&& strcmp(H[1].Pic, H[2].Pic) == 0
					&& strcmp(H[2].Pic, H[3].Pic) == 0
					&& strcmp(H[3].Pic, H[4].Pic) == 0)) { // if the suits are the same & card Nums are in order
		cout << "You have a Straight Flush!" << endl;
		money = bet * 1000;

		// Four of a Kind:
	} else if (H[0].Num == H[1].Num == H[2].Num == H[3].Num
			|| H[1].Num == H[2].Num == H[3].Num == H[4].Num) {
		// 4 of the cards have the same Num
		cout << "You have a Four of a Kind!" << endl;
		money = bet * 20;

		// Full House:
	} else if ((H[0].Num == H[1].Num && H[0].Num == H[2].Num
			&& H[3].Num == H[4].Num)
			|| (H[0].Num == H[1].Num && H[2].Num == H[3].Num
					&& H[2].Num == H[4].Num)) {
		// 3 of the cards have the same Num & the other 2 have the same Num
		cout << "You have a Full House!" << endl;
		money = bet * 10;

		// Flush:
	} else if (strcmp(H[0].Pic, H[1].Pic) == 0
			&& strcmp(H[1].Pic, H[2].Pic) == 0
			&& strcmp(H[2].Pic, H[3].Pic) == 0
			&& strcmp(H[3].Pic, H[4].Pic) == 0) {
		cout << "You have a Flush!" << endl;
		money = bet * 8;

		// Straight:
	} else if (H[1].Num == H[0].Num + 1 && H[2].Num == H[1].Num + 1
			&& H[3].Num == H[2].Num + 1 && H[4].Num == H[3].Num + 1) {
		// the card Nums are in order
		cout << "You have a Straight!" << endl;
		money = bet * 6;

		// Three of a Kind:
	} else if (H[0].Num == H[1].Num == H[2].Num
			|| H[1].Num == H[2].Num == H[3].Num
			|| H[2].Num == H[3].Num == H[4].Num) {
		// 3 of the cards have the same Num
		cout << "You have a Three of a Kind!" << endl;
		money = bet * 4;

		// Two Pair:
	} else if ((H[0].Num == H[1].Num && H[2].Num == H[3].Num)
			|| (H[1].Num == H[2].Num && H[3].Num == H[4].Num)
			|| (H[0].Num == H[1].Num && H[3].Num == H[4].Num)) {
		// 2 pairs of cards have the same Num
		cout << "You have a Two Pair!" << endl;
		money = bet * 2;

		// Jack or Better (High Card):
	} else if ((linearSearch(H, 1) > 0) || (linearSearch(H, 11) > 0)
			|| (linearSearch(H, 12) > 0) || (linearSearch(H, 13) > 0)) {
		// there is a J, Q, K, A in the hand
		cout << "You have a High Card!" << endl;
		money = bet * 1;

	} else {
		cout << "You got nothing..." << endl;
		money = (-1.0) * bet; // winnings become negative

	}

	return money; // returns amount of money won
}

// See if the value is in the array
int Poker::linearSearch(Card A[], int num) {
	unsigned int index = 0; // Holds the index.
// While the index is less than the number of values (13).
	while (index < 13) {
		// If the array value at the index is equal to the target, the index is returned.
		if (A[index].Num == num)
			return index;
		index++;
	}
	return -1;
}


