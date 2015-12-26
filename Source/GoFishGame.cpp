// GoFishGame.cpp
// Created by Evan Almonte
//
#include "GoFishGame.hpp"

const int GoFishGame::defaultNumOfPlayers = 2;

GoFishGame::GoFishGame( ) : theDeck(Deck(52)), numOfPlayers(defaultNumOfPlayers),
							thePlayers(new Player[defaultNumOfPlayers]) { }

GoFishGame::GoFishGame(int numOfPlayers) : theDeck(Deck(52)), numOfPlayers(numOfPlayers) {
	if(numOfPlayers < 2) {
		this->numOfPlayers = defaultNumOfPlayers;
	}
	thePlayers = new Player[this->numOfPlayers];
}
