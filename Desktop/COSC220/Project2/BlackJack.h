/*
 * BlackJack.h
 *
 *  Created on: Nov 25, 2020
 *      Author: kalynhowes
 */

#ifndef BLACKJACK_H_
#define BLACKJACK_H_
#include "Card.h"

class BlackJack : public Card {

public:

	int winningMoney = 0;

	BlackJack();
	int playBlackJack(int);
	int cardSum(vector<Card>);
	int winnings(int, int, int);

};

#endif /* BLACKJACK_H_ */
