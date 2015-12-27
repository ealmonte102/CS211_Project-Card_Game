// GoFishGame.cpp
// Created by Evan Almonte
//
#include "GoFishGame.hpp"

using std::cout;
using std::cin;
using std::string;

namespace GoFishGameUtils {
	bool arePlayerHandsEmpty (const Player* const thePlayers, int size);
	void displayOtherPlayers (const Player* const thePlayers, int size, int currentPlayer);
	int choosePlayer (const Player* const thePlayers, int size, int currentIndex);
}

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
	using namespace GoFishGameUtils;
	//Commented out, used for testing purposes.
	/*
	theDeck.shuffle ( );
	initPlayers ( );
	while (theDeck.getCount ( ) != 0) {
		for (int playerIndex = 0; playerIndex < numOfPlayers; ++playerIndex) {
			system("cls");
			cout << "It's your turn " << thePlayers[playerIndex].getName ( ) << "\n";
			displayOtherPlayers(thePlayers, numOfPlayers, playerIndex);
			cout << "Who would you like to take a card from?\n";
			cout << "Please choose a player: ";
			int playerChosen = choosePlayer (thePlayers, numOfPlayers, playerIndex);
			cout << "You chose player #" << playerChosen + 1 
				<< ": " + thePlayers[playerChosen].getName()
				<< "What card would you like to take? ";
			system ("pause");
		}
	}
	while (! arePlayerHandsEmpty(thePlayers, numOfPlayers)) {
		
	}
	*/
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


namespace GoFishGameUtils {
	bool arePlayerHandsEmpty (const Player* const thePlayers, int size) {
		for (int i = 0; i < size; ++i) {
			if(! thePlayers[i].handIsEmpty()) {
				return false;
			}
		}
		return true;
	}

	void displayOtherPlayers(const Player* const thePlayers, int size, int currentPlayer) {
		int count = 0;
		for (int i = 0; i < size; ++i) {
			if (i != currentPlayer) {
				cout << ++count << ") " + thePlayers[i].getName ( ) + "\n";
			}
		}
	}

	int choosePlayer(const Player* const thePlayers, int size, int currentIndex) {
		int chosen = 0;
		do {
			while (! (cin >> chosen)) {
				cin.clear ( );
				cin.ignore (10000, '\n');
			}
			if (chosen - 1 == currentIndex) { return chosen; }
		} while (chosen < 1 || chosen > size - 1);
		return chosen - 1;
	}
}