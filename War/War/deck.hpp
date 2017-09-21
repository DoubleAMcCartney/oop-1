#pragma once

#include <utility>
#include <iomanip>
#include <random>
#include <chrono>
#include <algorithm>

class Deck {
public:
	Deck();

	void makeStandardDeck();
	void shuffle();
	void printDeck();
	void takeCard(Card);
	void takeDeck(Deck*);
	void empty();
	Card giveCard();
	bool isEmpty();
	std::_Vector_iterator<std::_Vector_val<std::_Simple_types<Card>>> getBegin();
	std::_Vector_iterator<std::_Vector_val<std::_Simple_types<Card>>> getEnd();

private:
	std::vector<Card> deck;
};

void Deck::makeStandardDeck() {
	for (int r = Ace; r <= King; ++r) {
		for (int s = Diamond; s <= Spade; ++s) {
			Card c{ static_cast<Rank>(r), static_cast<Suit>(s) };
			deck.push_back(c);
		};
	};
}

Deck::Deck() {
	deck.reserve(52);
}

void Deck::printDeck() {
	for (int i = 0; i < 52; i++) {
		std::cout << deck[i] << '\n';
	};
}

void Deck::takeCard(Card c) {
	deck.push_back(c);
}

void Deck::takeDeck(Deck *d) {
	deck.insert(deck.end(), d->getBegin(), d->getEnd());
}

void Deck::empty() {
	deck.clear();
}

Card Deck::giveCard() {
	Card c = deck.back();
	deck.pop_back();
	return c;
}

void Deck::shuffle() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}

bool Deck::isEmpty() {
	if (deck.size() == 0) {
		return true;
	}
	else {
		return false;
	}
}

std::_Vector_iterator<std::_Vector_val<std::_Simple_types<Card>>> Deck::getBegin() {
	return deck.begin();
}

std::_Vector_iterator<std::_Vector_val<std::_Simple_types<Card>>> Deck::getEnd() {
	return deck.end();
}