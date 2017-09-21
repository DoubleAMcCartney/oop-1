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
	while (true) {
		//Each player plays a card
		Card c1 = p1.playCard();
		loot.takeCard(c1); //add card to loot
		std::cout << "Player1 card: " << c1 << '\n';
		Card c2 = p2.playCard();
		loot.takeCard(c2); //add card to loot
		std::cout << "Player2 card: " << c2 << '\n';

		if (c1 == c2) { //check for war
			war = true;
			std::cout << "War!\n";
		}
		else if (c1 > c2) {
			std::cout << "Player1 wins";
			//give p1 loot
		}
		else {
			std::cout << "Player2 wins";
			//give p2 loot
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
				std::cout << "War again!";
			}
			else if (c4 > c6) {
				std::cout << "Player1 wins!";
				war = false;
				//give p1 loot

			}
			else {
				std::cout << "Player2 wins this round!";
				war = false;
				//give p2 loot

			}
		}

		//check for empty hand / end of game
		if (p1.lost()) {
			std::cout << "Player1 is out of cards! Player2 Wins!";
			break;
		}
		else if (p2.lost()) {
			std::cout << "Player2 is out of cards! Player1 Wins!";
			break;
		}
	}

	std::cin.get();

	return 0;
}
