#ifndef CARD_H_
#define CARD_H_

class Card {

private:
	struct ACard {
		int Num;
		char Pic[4];
	};

	ACard Cards[52];

	const char spade[4]="\xe2\x99\xa0";
	const char club[4]= "\xe2\x99\xa3";
	const char heart[4] = "\xe2\x99\xa5";
	const char diamond[4]="\xe2\x99\xa6";

	int NextCard = 0;

public:

	Card();
	void ShuffleCards();
	ACard GetCard();

	void CardAce(const char []);
	void CardTwo(const char []);
	void CardThree(const char []);
	void CardFour(const char []);
	void CardFive(const char []);
	void CardSix(const char []);
	void CardSeven(const char []);
	void CardEight(const char []);
	void CardNine(const char []);
	void CardTen(const char []);
	void CardJack(const char []);
	void CardQueen(const char []);
	void CardKing(const char []);

};

#endif /* CARD_H_ */
