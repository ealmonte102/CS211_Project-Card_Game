#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Card.hpp"
#include "Hand.hpp"

class Card;
class Player {
public:
	Player ( );
	Player (std::string name, bool isCPU);
	// Return the players current score.
	int getScore ( ) const;
	// Returns the name of the player.
	std::string getName ( ) const;
	// Returns false if isCPU is true, otherwise returns true.
	bool isHuman ( ) const;
	// Inserts a card into a players hand in ascending order.
	bool handIsEmpty ( ) const;
	void addCard (Card* cardToAdd);
	// Returns -1 if card is not in calling objects hand, 0 if card is not in other players hand
	// 1 if card is in other players hand.
	int askForCard (Player& otherPlayer, Card::Suits aSuit, Card::Ranks aRank);
	// Sets the player's name to the passed parameter.
	void setName (std::string name);
	// Evaluates the players hand adding 1 point to the score per 4 similar cards.
	// Removes the group of cards found from the players hand.
	void evaluateHand ( );
	friend std::ostream& operator<<(std::ostream& output, const Player& aPlayer);
private:
	std::string name;
	bool isCPU;
	Hand playerHand;
	int score;
};

#endif //PLAYER_HPP

