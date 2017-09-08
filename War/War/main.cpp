//Simulation of War card game

#include <iostream>
#include <vector>
#include "card.hpp"




class Deck {
	public:
		Deck();
		void shuffle();
		Card deal();
	protected:
		Card deck[52];
};

class Player {

};

int main(){
	std::vector<Card> cards(52);
	int i = 0;
	for (Rank r = Ace; r <= King; static_cast<Rank>(static_cast<int>(r) + 1)) {
	  for (Suit s = heart; s <= spade; static_cast<Suit>(static_cast<int>(s) + 1))
	    cards[i++] = Card {r, s};
	}

	return 0;
}
