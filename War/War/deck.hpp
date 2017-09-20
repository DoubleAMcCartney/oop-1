#pragma once

#include <utility>
#include <iomanip>
#include <random>
#include <chrono>
#include <algorithm>
#include "card.hpp"

class Deck {
public:
	Deck();

	void shuffle();
	void showDeck();

private:
	std::vector<Card> deck;
};

Deck::Deck() {
	deck.reserve(52);
	for (int r = Ace; r <= King; ++r) {
		for (int s = Diamond; s <= Spade; ++s) {
			Card c{ static_cast<Rank>(r), static_cast<Suit>(s) };
			deck.push_back(c);
		};
	};
}

void Deck::showDeck() {
	for (int i = 0; i < 52; i++) {
		std::cout << deck[i] << '\n';
	};
}

void Deck::shuffle() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}