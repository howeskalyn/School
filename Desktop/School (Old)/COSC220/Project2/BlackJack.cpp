/*
 * BlackJack.cpp
 *
 *  Created on: Nov 25, 2020
 *      Author: kalynhowes
 */

#include "BlackJack.h"
#include "Card.h"
#include "Deck.h"
#include <vector>
#include <iostream>
using namespace std;

BlackJack::BlackJack() {
}

int BlackJack::playBlackJack(int bet) {
	//int winnings = 0;

	Deck D;
	D.shuffleDeck();

	// Create Hand storage for player & dealer
	vector<Card> pHand;
	vector<Card> dHand;
	Card C;

	// fill player's Hand with 2 cards
	for (int i = 0; i < 2; i++) {
		pHand.push_back(D.GetCard());
	}
	// fill dealer's Hand with 2 cards
	for (int i = 0; i < 2; i++) {
		dHand.push_back(D.GetCard());
	}

	// player opens both cards
	cout << "Player's Cards: " << endl;
	for (int i = 0; i < pHand.size(); i++)
		C.displayCard(pHand[i].Num, pHand[i].Pic);

	// dealer opens only one card
	cout << "Dealer's First Card: " << endl;
	C.displayCard(dHand[0].Num, dHand[0].Pic);

	// if dealers open card is an Ace, ask for an insurance bet
	char ins = ' ';
	int insurance = 0;
	if (dHand[0].Num == 1) {
		cout << "Would you like to place an insurance bet? (Y/N) ";
		cin >> ins;
		if (ins == 'Y' || ins == 'y') {
			insurance = bet / 2;
			if (dHand[1].Num == 10) {
				cout << "The dealer got BlackJack!" << endl;
				winningMoney = insurance * 2;
			}
		}
		// if the dealer's card in not an Ace, game play continues
	} else {

		// check for inital BlackJack
		int pCardSum = cardSum(pHand);
		if (pCardSum == 21) {
			cout << "You got BlackJack!\nYou win 1.5x your bet!" << endl;
			winningMoney = 1.5 * bet;
		} else {

			// continue play until the player holds(1), hit(0)
			int hitOrHold = 0;
			while (hitOrHold < 1) {
				cout << "Would you like to hit(0) or hold(1)? ";
				cin >> hitOrHold;

				// if they want a hit, a card is added to their hand and their hand is displayed again
				if (hitOrHold == 0) {
					pHand.push_back(D.GetCard());
					cout << "Player's Cards: " << endl;
					for (int i = 0; i < pHand.size(); i++)
						C.displayCard(pHand[i].Num, pHand[i].Pic);
				} else {
					pCardSum = cardSum(pHand);
					cout << "Your card sum is: " << pCardSum << endl;
				}
			}

			// determine winnings of play
			cout << "Dealer's second card: " << endl;
			C.displayCard(dHand[1].Num, dHand[1].Pic); // display second dealer card
			int dCardSum = cardSum(dHand); // find sum of dealers cards

			// while dealer's sum is 16 or less, they have to take another card
			while (dCardSum <= 16) {
				dHand.push_back(D.GetCard()); // another card is added & displayed
				cout << "Dealer's next card: " << endl;
				C.displayCard(dHand[dHand.size() - 1].Num,
						dHand[dHand.size() - 1].Pic);
				dCardSum = cardSum(dHand); // re-calculate sum of dealers hand
			}

			winningMoney = winnings(pCardSum, bet, dCardSum);
		}

	}

	return winningMoney;
}

// determines the sum of the players hand
int BlackJack::cardSum(vector<Card> hand) {
	int cardSum = 0; //sum of cards in players hand

	for (int i = 0; i < hand.size(); i++) {
		// if the card is a Jack, Queen, or King, 10 is added to the sum
		if (hand[i].Num == 11 || hand[i].Num == 12 || hand[i].Num == 13)
			cardSum += 10;
		// if the card is an ace, the player has an option of it being worth 1 or 11
		else if (hand[i].Num == 1) {
			int aceScore = 0;
			cout << "Would you like the Ace to be a score of 1 or 11? ";
			cin >> aceScore;
			cardSum += aceScore;
			// otherwise, the number value is added to the card sum
		} else
			cardSum += hand[i].Num;
	}

	return cardSum;
}

// determines winnings amount for the player based on their hand and the dealer's
int BlackJack::winnings(int pCardSum, int bet, int dCardSum) {
	int money = 0;

// if the player has BlackJack, they win 1.5x their bet
	if (pCardSum == 21) {
		cout << "You got BlackJack!\nYou win 1.5x your bet!" << endl;
		money = 1.5 * bet;

		// if the player's sum is higher than the dealers but not a bust(over 21), they win their bet
	} else if (pCardSum > dCardSum && pCardSum <= 21) {
		cout << "Your sum of " << pCardSum
				<< " is higher than the dealer's sum of " << dCardSum
				<< "\nYou win your bet in rewards!" << endl;
		money = bet;

		// if the player's sum is less than the dealer's sum OR the player busts, they lose their money
	} else if ((pCardSum < dCardSum && pCardSum <= 21 && dCardSum <= 21) || (pCardSum > 21)) {
		if (pCardSum < dCardSum && pCardSum <= 21) {
			cout << "Your sum of " << pCardSum
					<< " was less than the dealer's sum of " << dCardSum
					<< "\nYou lose your bet..." << endl;
			money = (-1.0) * bet; // winnings become negat
		} else if (pCardSum > 21) {
			cout << "Your sum of " << pCardSum
					<< " was higher than 21... you busted.\nYou lose your bet..."
					<< endl;
			money = (-1.0) * bet; // winnings become negative
		}

		// if player gets same as dealer has, player does not lose any money
	} else if (pCardSum == dCardSum) {
		cout << "Your sum of " << pCardSum
				<< " is the same as the dealer's sum of " << dCardSum
				<< "\nYou don't lose any money." << endl;
		money = 0;

		// if dealer busts, every player wins twice their bet
	} else if (dCardSum > 21) {
		cout << "The dealer's sum of " << dCardSum
				<< " is higher than 21, you win twice your bet!" << endl;
		money = 2 * bet;
	}
	return money;
}

