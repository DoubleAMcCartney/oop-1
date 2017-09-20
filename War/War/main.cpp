//Simulation of War card game

#include <iostream>
#include <vector>
#include <string>
#include "card.hpp"
#include "deck.hpp"
#include "player.hpp"


int main(){
	Deck theDeck;
	theDeck.showDeck();
	std::cout << '\n';
	theDeck.shuffle();
	theDeck.showDeck();

	std::cin.get();

	return 0;
}
