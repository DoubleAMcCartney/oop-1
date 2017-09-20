#pragma once

class Player {
public:
	Player() = default;
	Card playCard();
	void giveCard(Card);

private:
	Deck hand;
};

Card Player::playCard() {
	return hand.giveCard();
}

void Player::giveCard(Card c) {

}