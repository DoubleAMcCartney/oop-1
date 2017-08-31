//Simulation of War card game

#include <iostream>

enum suits {diamond, heart, club, spade};

class card {
	public:
		card(int, suits); //rank, suit
		int getRank();
		suits getSuit();
	protected:
		int rank;
		suits suit;
	
};

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
