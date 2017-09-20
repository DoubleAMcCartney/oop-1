#pragma once

class Player {
public:
	Player() = default;
	Card playCard();

private:
	Deck hand;
};

Card Player::playCard() {
	return hand.getCard();
}