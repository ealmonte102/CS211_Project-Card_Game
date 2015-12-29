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
	Card chooseCard ();
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
		for (int i = 0; i < numOfPlayers; ++i) {
			startTurn (thePlayers[i], i, false);
		}
	}
	while (! arePlayerHandsEmpty(thePlayers, numOfPlayers)) {
		for (int i = 0; i < numOfPlayers; ++i) {
			startTurn (thePlayers[i], i, true);
		}
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

void GoFishGame::startTurn(Player& currentPlayer, int indexOfPlayer, bool isDeckEmpty) {
	bool cardFished = false;
	do {
		system ("cls");
		cout << "----------------------------------\n";
		cout << "Player #" << indexOfPlayer + 1 << "'s turn:\n"
			<< currentPlayer;
		cout << "----------------------------------\n";
		GoFishGameUtils::displayOtherPlayers (thePlayers, numOfPlayers, indexOfPlayer);
		cout << "Who would you like to take a card from? \n";
		int playerChosen = GoFishGameUtils::choosePlayer (thePlayers, numOfPlayers, indexOfPlayer);
		Card aCard = GoFishGameUtils::chooseCard ( );
		if(currentPlayer.askForCard(thePlayers[playerChosen], aCard)) {
			cout << "You took a " << aCard << " from "
				<< thePlayers[playerChosen].getName() << "\n";
			cardFished = true;
		} else if(! isDeckEmpty) {
			cout << "************\n"
				<< "  Go Fish!\n"
				<< "************\n";
			currentPlayer.addCard (theDeck.deal ( ));
			cardFished = false;
		} else {
			cardFished = false;
		}
		system ("pause");
	} while (cardFished);

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

	Card chooseCard( ) {
		int suitChosen = 0, rankChosen = 0;
		cout << "*************************\n";
		cout << "   Please select a suit  \n";
		cout << "*************************\n";
			cout << "1) Clubs\n"
			<< "2) Diamonds\n"
			<< "3) Hearts\n"
			<< "4) Spades\n";
		while(! (cin >> suitChosen) || suitChosen < 1 || suitChosen > 4) {
			cin.clear ( );
			cin.ignore (10000, '\n');
		}
		cout << "*************************\n";
		cout << "   Please select a rank  \n";
		cout << "*************************\n";
		cout << "Please select a rank:\n";
		cout << "1) Two\n"
			<< "2)  Three\n"
			<< "3)  Four\n"
			<< "4)  Five\n"
			<< "5)  Six\n"
			<< "6)  Seven\n"
			<< "7)  Eight\n"
			<< "8)  Nine\n"
			<< "9) Ten\n"
			<< "10) Jack\n"
			<< "11) Queen\n"
			<< "12) King\n"
			<< "13) Ace\n";
		while (!(cin >> rankChosen) || rankChosen < 1 || rankChosen > 13) {
			cin.clear ( );
			cin.ignore (10000, '\n');
		}
		Card::Suits suitAsEnum = static_cast<Card::Suits>(suitChosen - 1);
		Card::Ranks rankAsEnum = static_cast<Card::Ranks>(rankChosen - 1);
		return Card (suitAsEnum, rankAsEnum);
	}
}
