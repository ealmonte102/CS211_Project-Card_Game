#ifndef DECK_HPP
#define DECK_HPP

#include <iostream>

#include "Card.hpp"
#include "Stack.hpp"

class Deck {
public:
	Deck ( );

	Deck (int sizeOfDeck);

	Deck (const Deck& otherDeck);

	Card* deal ( ) const;

	int getCount ( ) const;

	void shuffle ( );

	friend std::ostream& operator<<(std::ostream&, const Deck&);

	Deck& operator=(const Deck& rhs);

	~Deck ( );

private:
	const static int NUM_OF_SHUFFLES;
	Stack<Card>* deck;
};

#endif