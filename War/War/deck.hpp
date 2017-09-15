#pragma once

#include <utility>

class Deck {
public:
	Deck();

	void shuffle();
	Card deal();

protected:
	Card deck[52];
};

Deck::Deck() {
	std::vector<Card> deck(52);
	int i = 0;
	for (Rank r = Ace; r <= King; static_cast<Rank>(static_cast<int>(r) + 1)) {
		for (Suit s = heart; s <= spade; static_cast<Suit>(static_cast<int>(s) + 1))
			deck[i++] = Card{ r, s };
	};
}

Card Deck::deal() {

}

void Deck::shuffle() {

}