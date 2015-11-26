#include "Card.hpp"
#include <iostream>

using std::ostream;
using std::string;

Card::Card ( ) : suit (CLUB), rank (TWO), value (0) {
	createCardName ( );
}

Card::Card (int n) : suit (CLUB), rank (TWO), value (n) {
	if (value < 0 || value > 51) {
		value = 0;
	}
	createCardName ( );
}

Card::Card (Suits s, Ranks r) : suit (s), rank (r), value (13 * s + r + 1) {
	createCardName();
}

Card::Card (Suits s, Ranks r, int v) : suit (s), rank (r), value (v) {
	createCardName ( );
}

Card::Suits Card::getSuit ( ) const {
	return suit;
}

Card::Ranks Card::getRank ( ) const {
	return rank;
}

int Card::getValue ( ) const {
	return value;
}

// Returns a negative value when the calling object's SUIT is smaller
// 0 when both SUITS are equal. Positive number when it's SUIT is larger.
int Card::compareBySuit (const Card& other) const {
	return  static_cast<int>(suit) - static_cast<int>(other.suit);
}

// Returns a negative value when the calling object's RANK is smaller.
// 0 when both RANKS are equal. Positive number when it's RANK is larger.
int Card::compareByRank (const Card& other) const {
	return static_cast<int>(rank) - static_cast<int>(other.rank);
}

int Card::compareByValue (const Card& other) const {
	return value - other.value;
}

void Card::createCardName ( ) {
	string cardName = "";
	switch (rank) {
		case TWO:
			cardName += "Two";
			break;
		case THREE:
			cardName += "Three";
			break;
		case FOUR:
			cardName += "Four";
			break;
		case FIVE:
			cardName += "Five";
			break;
		case SIX:
			cardName += "Six";
			break;
		case SEVEN:
			cardName += "Seven";
			break;
		case EIGHT:
			cardName += "Eight";
			break;
		case NINE:
			cardName += "Nine";
			break;
		case TEN:
			cardName += "Ten";
			break;
		case JACK:
			cardName += "Jack";
			break;
		case QUEEN:
			cardName += "Queen";
			break;
		case KING:
			cardName += "King";
			break;
		case ACE:
			cardName += "Ace";
			break;
		default:
			cardName += "Joker";
			break;
	}
	cardName += " of ";
	switch (suit) {
		case CLUB:
			cardName += "Clubs";
			break;
		case DIAMOND:
			cardName += "Diamonds";
			break;
		case HEART:
			cardName += "Hearts";
			break;
		case SPADE:
			cardName += "Spades";
			break;
		default:
			cardName = "Jokers";
			break;
	}
}

ostream& operator<<(ostream& output, const Card& currentCard) {
	return output << currentCard.cardName;
}