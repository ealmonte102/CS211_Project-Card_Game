// GoFishGame.cpp
// Created by Evan Almonte
//
#include "GoFishGame.hpp"
#include <cstdlib>
#include <vector>

using std::cout;
using std::cin;
using std::string;
using std::vector;

namespace GoFishGameUtils {
	int chooseRandomPlayer (int numOfPlayers, int currentIndex);
	Card chooseRandomCard (const Player& aPlayer);
	bool arePlayerHandsEmpty (const Player* const thePlayers, int size);
	void displayOtherPlayers (const Player* const thePlayers, int size, int currentPlayer);
	int choosePlayer (const Player* const thePlayers, int size, int currentIndex);
	Card chooseCard ();
}

const int GoFishGame::defaultNumOfPlayers = 2;

const int GoFishGame::startingHand = 5;

GoFishGame::GoFishGame( ) : theDeck(Deck(52)), thePlayers(new Player[defaultNumOfPlayers]),
							numOfPlayers(defaultNumOfPlayers) { }

GoFishGame::GoFishGame(int numOfPlayers) : theDeck(Deck(52)), numOfPlayers(numOfPlayers) {
	if(numOfPlayers < 2) {
		this->numOfPlayers = defaultNumOfPlayers;
	}
	thePlayers = new Player[this->numOfPlayers];
}

GoFishGame::~GoFishGame( ) {
	delete[] thePlayers;
}

void GoFishGame::play( ) const {
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
		if (++playerIndex == numOfPlayers) {
			playerIndex = 0;
		}
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
	system ("cls");
	vector<int> winners = getWinners();
	if(winners.size() > 1) {
		cout << "*********************************************\n"
			<<  "                   Tie!\n"
			<<  "*********************************************\n";
	} else {
		cout << "*********************************************\n"
			<<  "                   Winner!\n"
			<<  "*********************************************\n";
	}
	cout << "Final Score: " << thePlayers[winners[0]].getScore ( ) << "\n";
	for (int i = 0; i < winners.size(); ++i) {
		cout << "Congratulations Player #" << winners[i] + 1
			<< ": " << thePlayers[winners[i]].getName ( ) << "\n";
	}
}

void GoFishGame::updateEmptyHands( ) const {
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

void GoFishGame::initPlayers( ) const {
	for (int i = 0; i < numOfPlayers; ++i) {
		cout << "Please enter a name for player " << i + 1 << ": ";
		string name;
		getline (cin, name);
		thePlayers[i].setName (name);
		cout << "Is the player a CPU(Y/N)? ";
		char isCPU = true;
		cin.get ( );
		cin.ignore ( );
		switch(isCPU) {
			case 'Y':
			case 'y':
				break;
			case 'N':
			case 'n':
				isCPU = false;
				break;
			default:
				break;
		}
		thePlayers[i].setCPUStatus (isCPU);
	}
	initPlayerHands ( );
}

void GoFishGame::initPlayerHands ( ) const {
	for (int i = 0; i < numOfPlayers; ++i) {
		for (int j = 0; j < startingHand; ++j) {
			thePlayers[i].addCard (theDeck.deal ( ));
		}
	}
}

void GoFishGame::startTurn(Player& currentPlayer, int indexOfPlayer, bool isDeckEmpty) const {
	bool cardFished = false;
	if (currentPlayer.isHuman ( )) {
		do {
			system ("cls");
			cout << "---------------------------------------------\n";
			cout << "Player #" << indexOfPlayer + 1 << "'s turn:\n"
				<< currentPlayer;
			cout << "---------------------------------------------\n";
			GoFishGameUtils::displayOtherPlayers (thePlayers, numOfPlayers, indexOfPlayer);
			cout << "Who would you like to take a card from? \n";
			int playerChosen = GoFishGameUtils::choosePlayer (thePlayers, numOfPlayers, indexOfPlayer);
			cout << "You chose " << thePlayers[playerChosen].getName ( ) << "\n";
			Card aCard = GoFishGameUtils::chooseCard ( );
			if (currentPlayer.askForCard (thePlayers[playerChosen], aCard)) {
				cout << "You took a " << aCard << " from "
					<< thePlayers[playerChosen].getName ( ) << "\n";
				cardFished = true;
			} else if (!isDeckEmpty) {
				cout << "*********************************************\n"
					<< "                   Go Fish!                  \n"
					<< "*********************************************\n";
				currentPlayer.addCard (theDeck.deal ( ));
				cardFished = false;
			}  else {
				cardFished = false;
			}
			system ("pause");
		} while (cardFished);
	} else {
		int playerChosen;
		Card cardChosen;
		do {
			system ("cls");
			cout << "---------------------------------------------\n";
			cout << "Player #" << indexOfPlayer + 1 << "'s turn:\n"
				<< currentPlayer;
			cout << "---------------------------------------------\n";
			playerChosen = GoFishGameUtils::chooseRandomPlayer(numOfPlayers, indexOfPlayer);
			cardChosen = GoFishGameUtils::chooseRandomCard (currentPlayer);
			cout << "The CPU " << currentPlayer.getName ( )
				<< " tries to take a " << cardChosen << " from "
				<< "Player # " << playerChosen + 1 << " "
				<< thePlayers[playerChosen].getName ( ) << "\n";
			if(currentPlayer.askForCard(thePlayers[playerChosen], cardChosen)) {
				cardFished = true;
				cout << "The CPU is succesful.\n";
			} else if (!isDeckEmpty) {
				cardFished = false;
				cout << "*********************************************\n"
					<< "                   Go Fish!                  \n"
					<< "*********************************************\n";
				currentPlayer.addCard (theDeck.deal ( ));
			} else {
				cardFished = false;
			}
			system ("pause");
		} while (cardFished);
	}
	currentPlayer.evaluateHand ( );
	updateEmptyHands ( );
}

namespace GoFishGameUtils {
	int chooseRandomPlayer(int numOfPlayers, int currentIndex) {
		int randIndex;
		do {
			randIndex = rand ( ) % numOfPlayers;
		} while (randIndex == currentIndex);
		return randIndex;
	}

	Card chooseRandomCard(const Player& aPlayer) {
		Card randomCard;
		Card::Suits randSuit;
		Card::Ranks randRank;
		do {
			randSuit = static_cast<Card::Suits>(rand ( ) % 4);
			randRank = static_cast<Card::Ranks>(rand ( ) % 13);
			randomCard = Card (randSuit, randRank);
		} while (! aPlayer.isRankInHand (randomCard));
		return randomCard;
	}

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
		cout << "*********************************************\n";
		cout << "             Please select a rank\n";
		cout << "*********************************************\n";
		cout << "Please select a rank:\n";
		cout <<"2) Two\n"
			<< "3) Three\n"
			<< "4) Four\n"
			<< "5) Five\n"
			<< "6) Six\n"
			<< "7) Seven\n"
			<< "8) Eight\n"
			<< "9) Nine\n"
			<< "10) Ten\n"
			<< "11) Jack\n"
			<< "12) Queen\n"
			<< "13) King\n"
			<< "14) Ace\n";
		while (!(cin >> rankChosen) || rankChosen < Card::TWO + 2 || rankChosen > Card::ACE + 2) {
			cin.clear ( );
			cin.ignore (10000, '\n');
		}
		cout << "*********************************************\n";
		cout << "             Please select a suit\n";
		cout << "*********************************************\n";
		cout <<"1) Clubs\n"
			<< "2) Diamonds\n"
			<< "3) Hearts\n"
			<< "4) Spades\n";
		while (!(cin >> suitChosen) || suitChosen < 1 || suitChosen > 4) {
			cin.clear ( );
			cin.ignore (10000, '\n');
		}
		Card::Suits suitAsEnum = static_cast<Card::Suits>(suitChosen - 1);
		Card::Ranks rankAsEnum = static_cast<Card::Ranks>(rankChosen - 2);
		return Card (suitAsEnum, rankAsEnum);
	}
}
