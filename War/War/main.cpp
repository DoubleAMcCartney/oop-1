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

	bool war = false;

	//while the deck is !empty, deal to p1 and p2
	while (!theDeck.isEmpty) {
		p1.giveCard(theDeck.takeCard);
		p2.giveCard(theDeck.takeCard);
	}

	//Each player plays a card
	Card c1 = p1.playCard();
	std::cout << c1;
	Card c2 = p2.playCard();
	std::cout << c2;

	//check for war
	if (c1 == c2) { 
		war = true;
	}
	while (war) {

	}
	//check for winner of round
	//check for empty hand / end of game

	std::cin.get();

	return 0;
}
