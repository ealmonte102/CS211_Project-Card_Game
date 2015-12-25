// Player.cpp
// Created by Evan Almonte
//
#include "Player.hpp"

using std::cout;

Player::Player(std::string name, bool isCPU) : name(name), isCPU(isCPU), score(0) {}

int Player::getScore ( ) const { return score; }

std::string Player::getName ( ) const { return name; }

bool Player::isHuman ( ) const { return !isCPU; }

void Player::addCard (Card* cardToAdd) { playerHand.insert (cardToAdd); }

bool Player::askForCard(Player& otherPlayer, Card::Suits aSuit, Card::Ranks aRank) {
	Card cardToFind (aSuit, aRank);
	if (playerHand.find (&cardToFind) == nullptr) { return false; };
	Card* cardFound = otherPlayer.playerHand.find (&cardToFind);
	if (cardFound == nullptr) { return false; }
	playerHand.insert (cardFound);
	otherPlayer.playerHand.remove (cardFound);
	return true;
}

void Player::evaluateHand( ) {
	score = playerHand.evaluate();
}
