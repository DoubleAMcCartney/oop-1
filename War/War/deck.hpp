#pragma once

#include <utility>
#include <random>
#include <chrono>
#include <algorithm>

class Deck {
public:
	Deck();

	void shuffle();
	void deal();

private:
	std::vector<Card> deck;
};

Deck::Deck() {
	int i = 0;
	for (Rank r = Ace; r <= King; static_cast<Rank>(static_cast<int>(r) + 1)) {
		for (Suit s = Heart; s <= Spade; static_cast<Suit>(static_cast<int>(s) + 1))
			deck[i++] = Card{ r, s };
	};
}

void Deck::deal() {
	for (int i = 0; i < 52; i++) {
		std::cout << deck[i];
	};
}

void Deck::shuffle() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}