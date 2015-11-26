#include "Card.hpp"

#include <iostream>

using std::ostream;
using std::string;

Card::Card ( ) : suit (CLUB), rank (TWO), value (0), cardName (createCardName ( )) { }

Card::Card (int n) : suit (CLUB), rank (TWO), value (n), cardName (createCardName ( )) {
	if (value < 0 || value > 51) {
		value = 0;
	}
}

Card::Card (Suits s, Ranks r) : suit (s), rank (r), value (13 * s + r + 1), cardName (createCardName ( )) { }

Card::Card (Suits s, Ranks r, int v) : suit (s), rank (r), value (v) { }

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

std::string Card::createCardName ( ) {
	string tempName = "";
	switch (rank) {
		case TWO:
			tempName += "Two";
			break;
		case THREE:
			tempName += "Three";
			break;
		case FOUR:
			tempName += "Four";
			break;
		case FIVE:
			tempName += "Five";
			break;
		case SIX:
			tempName += "Six";
			break;
		case SEVEN:
			tempName += "Seven";
			break;
		case EIGHT:
			tempName += "Eight";
			break;
		case NINE:
			tempName += "Nine";
			break;
		case TEN:
			tempName += "Ten";
			break;
		case JACK:
			tempName += "Jack";
			break;
		case QUEEN:
			tempName += "Queen";
			break;
		case KING:
			tempName += "King";
			break;
		case ACE:
			tempName += "Ace";
			break;
		default:
			tempName += "Joker";
			break;
	}
	tempName += " of ";
	switch (suit) {
		case CLUB:
			tempName += "Clubs";
			break;
		case DIAMOND:
			tempName += "Diamonds";
			break;
		case HEART:
			tempName += "Hearts";
			break;
		case SPADE:
			tempName += "Spades";
			break;
		default:
			tempName = "Jokers";
			break;
	}
	return tempName;
}

ostream& operator<<(ostream& output, const Card& currentCard) {
	return output << currentCard.cardName;
}