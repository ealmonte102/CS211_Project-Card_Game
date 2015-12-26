#ifndef GOFISHGAME_HPP
#define GOFISHGAME_HPP

#include "Deck.hpp"
#include "Player.hpp"

class GoFishGame {
public:
	GoFishGame ( );
	GoFishGame (int numOfPlayers);
	void play ( );
private:
	Deck theDeck;
	static const int defaultNumOfPlayers;
	int numOfPlayers;
	Player* thePlayers;
};

#endif //GOFISHGAME_HPP

