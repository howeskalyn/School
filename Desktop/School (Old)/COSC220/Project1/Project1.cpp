#include <iostream>
using namespace std;

#include "Card.h"

void print(int, char[], Card);

int main() {

	Card x;
	x.ShuffleCards();

	int n = 0;
	char a[4];

	// display 2 cards
	for (int i = 0; i < 2; i++) {
		// set function parameters to send to print
		n = x.GetCard().Num;
		for (int i = 0; i < 4; i++) {
			a[i] = x.GetCard().Pic[i];
		}
		print(n, a, x);
	}

	x.ShuffleCards();

	// display 3 cards
	for (int i = 0; i < 3; i++) {
		n = x.GetCard().Num;
		for (int i = 0; i < 4; i++) {
			a[i] = x.GetCard().Pic[i];
		}
		print(n, a, x);
	}

	x.ShuffleCards();

	// display 4 cards
	for (int i = 0; i < 4; i++) {
		n = x.GetCard().Num;
		for (int i = 0; i < 4; i++) {
			a[i] = x.GetCard().Pic[i];
		}
		print(n, a, x);
	}

	x.ShuffleCards();

	// display 5 cards
	for (int i = 0; i < 5; i++) {
		n = x.GetCard().Num;
		for (int i = 0; i < 4; i++) {
			a[i] = x.GetCard().Pic[i];
		}
		print(n, a, x);
	}

	return 0;
}

void print(int n, char a[], Card x) {
	if (n == 1)
		x.CardAce(a);
	else if (n == 2)
		x.CardTwo(a);
	else if (n == 3)
		x.CardThree(a);
	else if (n == 4)
		x.CardFour(a);
	else if (n == 5)
		x.CardFive(a);
	else if (n == 6)
		x.CardSix(a);
	else if (n == 7)
		x.CardSeven(a);
	else if (n == 8)
		x.CardEight(a);
	else if (n == 9)
		x.CardNine(a);
	else if (n == 10)
		x.CardTen(a);
	else if (n == 11)
		x.CardJack(a);
	else if (n == 12)
		x.CardQueen(a);
	else if (n == 13)
		x.CardKing(a);
}
