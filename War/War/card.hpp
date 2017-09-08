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

	int getRank();

	Suit getSuit();

protected:
	Rank rank;
	Suit suit;

};

