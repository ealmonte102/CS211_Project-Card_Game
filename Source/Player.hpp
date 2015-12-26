#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Card.hpp"
#include "Hand.hpp"

class Card;
class Player {
public:
	Player ( );
	Player (std::string name, bool isCPU);
	int getScore ( ) const;
	std::string getName ( ) const;
	bool isHuman ( ) const;
	void addCard (Card* cardToAdd);
	//Returns -1 if card is not in calling objects hand, 0 if card is not in other players hand
	//1 if card is in other players hand.
	int askForCard (Player& otherPlayer, Card::Suits aSuit, Card::Ranks aRank);
	void evaluateHand ( );
	friend std::ostream& operator<<(std::ostream& output, const Player& aPlayer);
private:
	std::string name;
	bool isCPU;
	Hand playerHand;
	int score;
};

#endif //PLAYER_HPP

