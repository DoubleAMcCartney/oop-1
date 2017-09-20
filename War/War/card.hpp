#pragma once

#include <utility>

enum Suit { Diamond = 1, Heart, Club, Spade };
enum Rank { Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };

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

std::ostream& operator<<(std::ostream& os, Rank r)
{
	switch (r) {
	case Ace:
		os << 'A';
		break;
	case Two:
		os << '2';
		break;
	case Three:
		os << '3';
		break;
	case Four:
		os << '4';
		break;
	case Five:
		os << '5';
		break;
	case Six:
		os << '6';
		break;
	case Seven:
		os << '7';
		break;
	case Eight:
		os << '8';
		break;
	case Nine:
		os << '9';
		break;
	case Ten:
		os << 'T';
		break;
	case Jack:
		os << 'J';
		break;
	case Queen:
		os << 'Q';
		break;
	case King:
		os << 'K';
		break;
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, Suit s)
{
	switch (s) {
	case Heart:
		os << 'H';
		break;
	case Diamond:
		os << 'D';
		break;
	case Club:
		os << 'C';
		break;
	case Spade:
		os << 'S';
		break;
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, Card c)
{
	return os << c.getRank() << c.getSuit();
}

bool operator<(Card a, Card b)
{
	return a.getRank() < b.getRank();
}

bool operator>(Card a, Card b)
{
	return a.getRank() > b.getRank();
}

bool operator==(Card a, Card b)
{
	return a.getRank() == b.getRank();
}
