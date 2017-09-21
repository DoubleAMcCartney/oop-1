//Simulation of War card game

#include <iostream>
#include <vector>
#include <string>
#include "card.hpp"
#include "deck.hpp"
#include "player.hpp"


int main() {
	Deck theDeck;
	Deck loot;
	theDeck.makeStandardDeck();
	theDeck.shuffle();

	Player p1;
	Player p2;

	bool war = false;

	//while the deck is !empty, deal to p1 and p2
	while (!theDeck.isEmpty()) {
		p1.takeCard(theDeck.giveCard());
		p2.takeCard(theDeck.giveCard());
	}

	//Each player plays a card
	Card c1 = p1.playCard();
	std::cout << "Player1 card: " << c1 << '\n';
	Card c2 = p2.playCard();
	std::cout << "Player2 card: " << c2 << '\n';

	//check for war
	if (c1 == c2) { 
		war = true;
		loot.takeCard(c1);
		loot.takeCard(c2);
		std::cout << "War!\n";
	}
	while (war) {
		Card c3 = p1.playCard();
		Card c4 = p1.playCard();
		Card c5 = p2.playCard();
		Card c6 = p2.playCard();
		loot.takeCard(c3);
		loot.takeCard(c4);
		loot.takeCard(c5);
		loot.takeCard(c6);
		if (c4 == c6) {

		}
	}
	//check for winner of round
	//check for empty hand / end of game

	std::cin.get();

	return 0;
}
