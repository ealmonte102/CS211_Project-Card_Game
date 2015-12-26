// Player.cpp
// Created by Evan Almonte
//
#include "Player.hpp"
#include "Hand.hpp"
#include <iostream>

using std::cout;

Player::Player( ) : name(""), isCPU(false), score(0) {}

Player::Player(std::string name, bool isCPU) : name(name), isCPU(isCPU), score(0) {}

int Player::getScore ( ) const { return score; }

std::string Player::getName ( ) const { return name; }

bool Player::isHuman ( ) const { return !isCPU; }

bool Player::handIsEmpty( ) const {
	return playerHand.getSize ( ) == 0;
}

void Player::addCard (Card* cardToAdd) { playerHand.insert (cardToAdd); }

int Player::askForCard(Player& otherPlayer, Card::Suits aSuit, Card::Ranks aRank) {
	Card cardToFind (aSuit, aRank);
	if (playerHand.find (&cardToFind) == nullptr) { return -1; };
	Card* cardFound = otherPlayer.playerHand.find (&cardToFind);
	if (cardFound == nullptr) { return 0; }
	playerHand.insert (cardFound);
	otherPlayer.playerHand.remove (cardFound);
	return 1;
}

void Player::setName (std::string name) { this->name = name; }

void Player::evaluateHand( ) {
	score = playerHand.evaluate();
}

std::ostream& operator<<(std::ostream& output, const Player& aPlayer) {
	cout << "Player: " << aPlayer.name << "\n";
	cout << "CPU: " << (aPlayer.isCPU == true ? "true" : "false") << "\n";
	cout << "Score: " << aPlayer.score << "\n";
	cout << aPlayer.playerHand << "\n";
	return output;
}