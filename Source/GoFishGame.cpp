// GoFishGame.cpp
// Created by Evan Almonte
//
#include "GoFishGame.hpp"

using std::cout;
using std::cin;
using std::string;

const int GoFishGame::defaultNumOfPlayers = 2;

const int GoFishGame::startingHand = 5;

GoFishGame::GoFishGame( ) : theDeck(Deck(52)), numOfPlayers(defaultNumOfPlayers),
							thePlayers(new Player[defaultNumOfPlayers]) { }

GoFishGame::GoFishGame(int numOfPlayers) : theDeck(Deck(52)), numOfPlayers(numOfPlayers) {
	if(numOfPlayers < 2) {
		this->numOfPlayers = defaultNumOfPlayers;
	}
	thePlayers = new Player[this->numOfPlayers];
}

GoFishGame::~GoFishGame( ) {
	delete[] thePlayers;
}

void GoFishGame::play( ) {
	//Commented out, used for testing purposes.
	theDeck.shuffle ( );
	initPlayers ( );
	
}

void GoFishGame::displayPlayers( ) const {
	for (int i = 0; i < numOfPlayers; ++i) {
		cout << thePlayers[i] << "\n";
	}
}

void GoFishGame::initPlayers( ) {
	for (int i = 0; i < numOfPlayers; ++i) {
		cout << "Please enter a name for player " << i + 1 << ": ";
		string name;
		getline (cin, name);
	thePlayers[i].setName (name);
	}
	initPlayerHands ( );
}

void GoFishGame::initPlayerHands ( ) {
	for (int i = 0; i < startingHand; ++i) {
		for (int j = 0; j < numOfPlayers; ++j) {
			thePlayers[j].addCard (theDeck.deal ( ));
		}
	}
}
