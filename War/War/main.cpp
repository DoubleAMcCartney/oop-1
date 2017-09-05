//Simulation of War card game

#include <iostream>
#include card.hpp


//create card
card::card(int r, suits s){
	rank = r;
	suits = s;
}

class deck {
	public:
		void shuffle();
		card deal();
	protected:
		card deck[52];
};

class player {

};

int main{
	

	return 0;
}
