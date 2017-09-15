#pragma once

#include <utility>

enum Suit { diamond, heart, club, spade };
enum Rank { Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };

class Card {
public:
	Card() = default;
	Card(Rank r, Suit s)
		: rank(r), suit(s)
	{}
	Rank getRank();
	Suit getSuit();

private:
	Rank rank;
	Suit suit;
};

Rank Card::getRank() {
	return rank;
}

Suit Card::getSuit() {
	return suit;
}