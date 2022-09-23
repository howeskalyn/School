#include "Card.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

Card::Card() {
	// Spades
	for (int value = 1; value < 14; value++) {
		ACard temp;
		for (int i = 0; i < 4; i++) {
			temp.Pic[i] = spade[i];
		}
		temp.Num = value;
		Cards[value - 1] = temp;
	}

	// Clubs
	for (int value = 1; value < 14; value++) {
		ACard temp;
		for (int i = 0; i < 4; i++) {
			temp.Pic[i] = club[i];
		}
		temp.Num = value;
		Cards[value - 1] = temp;
	}

	// Hearts
	for (int value = 1; value < 14; value++) {
		ACard temp;
		for (int i = 0; i < 4; i++) {
			temp.Pic[i] = heart[i];
		}
		temp.Num = value;
		Cards[value - 1] = temp;
	}

	// Diamonds
	for (int value = 1; value < 14; value++) {
		ACard temp;
		for (int i = 0; i < 4; i++) {
			temp.Pic[i] = diamond[i];
		}
		temp.Num = value;
		Cards[value - 1] = temp;
	}
}

void Card::ShuffleCards() {
	srand(time(0));
	srand((unsigned) time( NULL));

	int k;
	ACard temp;

	for (int i = 0; i < 52; i++) {
		k = i + (rand() % (52 - i));
		temp = Cards[i];
		Cards[i] = Cards[k];
		Cards[k] = temp;
	}

	NextCard = 0;

}

Card::ACard Card::GetCard() {
	ACard ret = Cards[NextCard];
	NextCard++;
	return ret;
}

void Card::CardAce(const char Pic[]) {
	cout << "---------" << endl;
	cout << "|" << "A" << setw(7) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(7) << "A" << "|" << endl;
	cout << "---------";
}

void Card::CardTwo(const char Pic[]) {
	cout << "---------" << endl;
	cout << "|" << "2" << setw(7) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(7) << "2" << "|" << endl;
	cout << "---------";
}

void Card::CardThree(const char Pic[]) {
	cout << "---------" << endl;
	cout << "|" << "3" << setw(7) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(7) << "3" << "|" << endl;
	cout << "---------";

}

void Card::CardFour(const char Pic[]) {
	cout << "---------" << endl;
	cout << "|" << "4" << setw(7) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(7) << "4" << "|" << endl;
	cout << "---------";

}

void Card::CardFive(const char Pic[]) {
	cout << "---------" << endl;
	cout << "|" << "5" << setw(7) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(7) << "5" << "|" << endl;
	cout << "---------";

}

void Card::CardSix(const char Pic[]) {
	cout << "---------" << endl;
	cout << "|" << "6" << setw(7) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(7) << "6" << "|" << endl;
	cout << "---------";

}

void Card::CardSeven(const char Pic[]) {
	cout << "---------" << endl;
	cout << "|" << "7" << setw(7) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(7) << "7" << "|" << endl;
	cout << "---------";

}

void Card::CardEight(const char Pic[]) {
	cout << "---------" << endl;
	cout << "|" << "8" << setw(7) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(7) << "8" << "|" << endl;
	cout << "---------";

}

void Card::CardNine(const char Pic[]) {
	cout << "---------" << endl;
	cout << "|" << "9" << setw(7) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(7) << "9" << "|" << endl;
	cout << "---------";

}

void Card::CardTen(const char Pic[]) {
	cout << "---------" << endl;
	cout << "|" << "10" << setw(7) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(7) << "10" << "|" << endl;
	cout << "---------";

}

void Card::CardJack(const char Pic[]) {
	cout << "---------" << endl;
	cout << "|" << "J" << setw(7) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(7) << "J" << "|" << endl;
	cout << "---------";

}

void Card::CardQueen(const char Pic[]) {
	cout << "---------" << endl;
	cout << "|" << "Q" << setw(7) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(7) << "Q" << "|" << endl;
	cout << "---------";

}

void Card::CardKing(const char Pic[]) {
	cout << "---------" << endl;
	cout << "|" << "K" << setw(7) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(6) << Pic << setw(4) << "|" << endl;
	cout << "|" << setw(8) << "|" << endl;
	cout << "|" << setw(7) << "K" << "|" << endl;
	cout << "---------";

}
