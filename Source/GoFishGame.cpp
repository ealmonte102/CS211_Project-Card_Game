// GoFishGame.cpp
// Created by Evan Almonte
//
#include "GoFishGame.hpp"
#include <vector>

using std::cout;
using std::cin;
using std::string;
using std::vector;

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
	theDeck.shuffle ( );
	initPlayers ( );
	int playerIndex = 0;
	while (theDeck.getCount ( ) != 0) {
		startTurn (thePlayers[playerIndex], playerIndex, false);
		if(++playerIndex == numOfPlayers) {
			playerIndex = 0;
		}
	}
	while (! arePlayerHandsEmpty(thePlayers, numOfPlayers)) {
		startTurn (thePlayers[playerIndex], playerIndex, true);
	}
	displayWinners ( );
}

vector<int> GoFishGame::getWinners( ) const {
	int maxScore = 0;
	for (int i = 0; i < numOfPlayers; ++i) {
		int playerScore = thePlayers[i].getScore ( );
		if(playerScore > maxScore) {
			maxScore = playerScore;
		}
	}
	vector<int> winners;
	for (int i = 0; i < numOfPlayers; ++i) {
		if(thePlayers[i].getScore() == maxScore) {
			winners.push_back (i);
		}
	}
	return winners;
}

void GoFishGame::displayWinners( ) const {
	vector<int> winners = getWinners();
	if(winners.size() > 1) {
		cout << "************\n"
			<< "	Tie!\n"
			<< "************\n";
	} else {
		cout << "***********\n"
			<< "	Winner!\n"
			<< "***********\n";
	}
	for (int i = 0; i < winners.size(); ++i) {
		cout << "Congratulations Player #" << winners[i]
			<< "\t" << thePlayers[winners[i]].getName ( ) << " "
			<< "| Score: " << thePlayers[winners[i]].getScore ( ) << "\n";
	}
}

void GoFishGame::updateEmptyHands( ) {
	int cardsInDeck = theDeck.getCount ( );
	for (int i = 0; i < numOfPlayers; ++i) {
		if(thePlayers[i].handIsEmpty()) {
			for (int j = 0; j < 5 && cardsInDeck != 0; ++j, cardsInDeck--) {
				thePlayers[i].addCard (theDeck.deal ( ));
			}
		}
	}
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
	for (int i = 0; i < numOfPlayers; ++i) {
		for (int j = 0; j < startingHand; ++j) {
			thePlayers[i].addCard (theDeck.deal ( ));
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
		cout << "You chose " << thePlayers[playerChosen].getName ( ) << "\n";
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
	currentPlayer.evaluateHand ( );
	updateEmptyHands ( );
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
				cout << ++count << ") " << thePlayers[i].getName() << "\n";
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
		} while (chosen < 1 || chosen > size - 1);
		if(chosen <= currentIndex) {
			return chosen - 1;
		}
		return chosen;
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
