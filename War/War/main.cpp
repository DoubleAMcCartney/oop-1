//Simulation of War card game

#include <iostream>
#include <vector>
#include <string>
#include "card.hpp"
#include "deck.hpp"
#include "player.hpp"


int main() {
	Deck theDeck;
	theDeck.shuffle();

	Player p1;
	Player p2;

	//while the deck is !empty, deal to p1 and p2
	while (!theDeck.isEmpty) {
		p1.giveCard(theDeck.getCard);
		p2.giveCard(theDeck.getCard);
	}

	//Each player plays a card
	//check for war
	//check for winner of round
	//check for empty hand / end of game

	std::cin.get();

	return 0;
}
