﻿#ifndef GOFISHGAME_HPP
#define GOFISHGAME_HPP

#include "Deck.hpp"
#include "Player.hpp"
#include <vector>

class GoFishGame {
public:
	GoFishGame ( );
	GoFishGame (int numOfPlayers);
	~GoFishGame ( );
	void play ( ) const;
private:
	static const int startingHand;
	static const int defaultNumOfPlayers;
	Deck theDeck;
	Player* thePlayers;
	int numOfPlayers;
	
	std::vector<int> getWinners ( ) const;
	void displayWinners ( ) const;
	void updateEmptyHands ( ) const;
	void displayPlayers ( ) const;
	void initPlayers ( ) const;
	void initPlayerHands ( ) const;
	void startTurn (Player& currentPlayer, int index, bool isDeckEmpty) const;
};

#endif //GOFISHGAME_HPP

