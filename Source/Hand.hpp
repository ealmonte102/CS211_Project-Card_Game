#ifndef Hand_HPP
#define Hand_HPP

#include "Linkedlist.hpp"

class Card;
class Hand : public LinkedList<Card*> {
public:
	Hand ( );
	// Returns 1 for every group of 4 cards that are the same.
	int evaluate ( );

	friend std::ostream& operator<<(std::ostream& output, const Hand& aHand);
	
	//Returns true if a card with the same rank is found.
	bool findRank(Card& card) const;
private:
	// Removes a group of 4 cards from the hand.
	void removeGroup (Node* node);
	// Finds the first group of 4 cards in the hand.
	Node* findGroup () const;
};

#endif //Hand_HPP

