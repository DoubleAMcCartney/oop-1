#pragma once

class Player {
public:
	Player() = default;
	Card playCard();
	void takeCard(Card);
	void takeDeck(Deck*);
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

void Player::takeDeck(Deck *d) {
	hand.takeDeck(d);
	d->empty();
}

bool Player::lost() {
	return hand.isEmpty();
}