#ifndef GOFISHGAME_HPP
#define GOFISHGAME_HPP

#include "Deck.hpp"
#include "Player.hpp"

class GoFishGame {
public:
	GoFishGame ( );
	GoFishGame (int numOfPlayers);
	~GoFishGame ( );
	void play ( );
private:
	void displayPlayers ( ) const;
	void initPlayers ( );
	void initPlayerHands ( );
	void startTurn (Player& currentPlayer, int index, bool isDeckEmpty);
	static const int startingHand;
	Deck theDeck;
	static const int defaultNumOfPlayers;
	int numOfPlayers;
	Player* thePlayers;
};

#endif //GOFISHGAME_HPP

