#ifndef GOFISHGAME_HPP
#define GOFISHGAME_HPP

#include "Deck.hpp"
#include "Player.hpp"
#include <vector>

class GoFishGame {
public:
	GoFishGame ( );
	GoFishGame (int numOfPlayers);
	~GoFishGame ( );
	void play ( );
private:
	static const int startingHand;
	static const int defaultNumOfPlayers;
	Deck theDeck;
	Player* thePlayers;
	int numOfPlayers;
	
	std::vector<int> getWinners ( ) const;
	void updateEmptyHands ( );
	void displayPlayers ( ) const;
	void initPlayers ( );
	void initPlayerHands ( );
	void startTurn (Player& currentPlayer, int index, bool isDeckEmpty);
};

#endif //GOFISHGAME_HPP

