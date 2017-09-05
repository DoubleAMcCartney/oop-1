#pragma once

enum suits { diamond, heart, club, spade };

enum Rank {	Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };

class card {
public:
	card(int, suits); //rank, suit
	int getRank();
	suits getSuit();

protected:
	int rank;
	suits suit;

};