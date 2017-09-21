#pragma once

class Player {
public:
	Player() = default;
	Card playCard();
	void takeCard(Card);
	bool lost();

private:
	Deck hand;
};

Card Player::playCard() {
	return hand.giveCard();
}

void Player::takeCard(Card c) {
	hand.takeCard(c);
}

bool Player::lost() {
	return hand.isEmpty();
}