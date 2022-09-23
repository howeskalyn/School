//============================================================================
// Name        : Casino.cpp
// Author      : Kalyn Howes
// Date        : 12.8.2020
// Description : Gives the user an option to play Poker or BlackJack.
//============================================================================

#include <iostream>
#include "Poker.h"
#include "BlackJack.h"
using namespace std;

int main() {

	char choice = 'Y';
	int winnings = 0;
	cout << "\nWelcome to the Casino Game!" << endl;
	cout << "Do you wish to play a game? (Y/N): ";
	cin >> choice;

	if (choice == 'y' || choice == 'Y') {
		while (choice == 'y' || choice == 'Y') {

			int initialMoney = 0;
			cout << "Enter an amount of money to play with: $";
			cin >> initialMoney;

			int bet = 0;
			cout << "Enter an amount of money to bet with: $";
			cin >> bet;

			char choice2 = ' ';
			cout << "Do you want to play Poker(P) or BlackJack(B)? ";
			cin >> choice2;

			if (choice2 == 'P' || choice2 == 'p') {
				Poker p;
				winnings = p.playPoker(bet);
			} else if (choice2 == 'B' || choice2 == 'b') {
				BlackJack b;
				winnings = b.playBlackJack(bet);
			}

			cout << "\nYour initial balance was: $" << initialMoney << "."
					<< endl;
			cout << "Your bet was: $" << bet << endl;
			cout << "You won: $" << winnings << endl;
			cout << "Your current balance is: $" << initialMoney + winnings
					<< "." << endl;

			cout << "\nWould you like to play again? (Y/N)  ";
			cin >> choice;
		}

	} else {
		cout << "Qutting program..." << endl;
	}

}

