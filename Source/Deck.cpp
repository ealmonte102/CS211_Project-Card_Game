#include <iostream>
#include <cstdlib>

#include "Deck.hpp"
#include "Stack.hpp"
#include "Card.hpp"

using std::ostream;

const int Deck::NUM_OF_SHUFFLES = 100000;

Deck::Deck ( ) {
	deck = new Stack<Card>;
	int cap = deck->getTotalCapacity ( );
	int count = 0;
	for (int suit = Card::CLUB; suit <= Card::SPADE && count != cap; ++suit) {
		for (int rank = Card::TWO; rank <= Card::ACE && count != cap; ++rank, count++) {
			deck->push (new Card (static_cast<Card::Suits>(suit),
								  static_cast<Card::Ranks>(rank)));
		}
	}
}

Deck::Deck (int sizeOfDeck) {
	if (sizeOfDeck <= 0) {
		sizeOfDeck = 13;
	}
	deck = new Stack<Card> (sizeOfDeck);
	for (int count = 0, suit = Card::CLUB; suit <= Card::SPADE && count < sizeOfDeck;) {
		for (int rank = Card::TWO; rank <= Card::ACE && count < sizeOfDeck; ++count) {
			deck->push (new Card (static_cast<Card::Suits>(suit), static_cast<Card::Ranks>(rank)));
			++rank;
		}
		++suit;
		if (suit > Card::SPADE) {
			suit = Card::CLUB;
		}
	}
}

Deck::Deck (const Deck& otherDeck) {
	deck = new Stack<Card> (*otherDeck.deck);
}

Deck::~Deck ( ) {
	delete deck;
}

Card* Deck::deal ( ) const {
	return deck->pop ( );
}

int Deck::getCount ( ) const {
	return deck->getSize ( );
}

void Deck::shuffle ( ) const {
	int sizeOfDeck = getCount ( );
	Card** randomCards = new Card*[sizeOfDeck];
	for (int i = 0; i < sizeOfDeck; ++i) {
		randomCards[i] = deck->pop ( );
	}
	for (int i = 1; i <= NUM_OF_SHUFFLES; ++i) {
		int firstRandom = rand ( ) % sizeOfDeck;
		int otherRandom = rand ( ) % sizeOfDeck;
		Card* temp = randomCards[firstRandom];
		randomCards[firstRandom] = randomCards[otherRandom];
		randomCards[otherRandom] = temp;
	}

	for (int i = 0; i < sizeOfDeck; i++) {
		deck->push (randomCards[i]);
	}
	delete[] randomCards;
}

Deck& Deck::operator =(const Deck& rhs) {
	if (this != &rhs) {
		delete deck;
		deck = new Stack<Card> (*rhs.deck);
	}
	return *this;
}

ostream& operator <<(ostream& out, const Deck& d) {
	return out << *d.deck;
}