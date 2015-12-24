#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Card.hpp"
#include "Hand.hpp"
#include <string>

class Card;
class Player {
public:
	Player (std::string name, bool isCPU);
	int getScore ( ) const;
	std::string getName ( ) const;
	bool isHuman ( ) const;
	void addCard (Card* cardToAdd);
	bool askForCard (Player& otherPlayer, Card::Suits aSuit, Card::Ranks aRank);
	void evaluateHand ( );
private:
	std::string name;
	bool isCPU;
	Hand playerHand;
	int score;
};

#endif //PLAYER_HPP

