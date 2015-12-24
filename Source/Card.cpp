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

bool Card::operator==(const Card& rhs) const {
	return rank == rhs.rank;
}
bool Card::operator<(const Card& rhs) const {
	return rank < rhs.rank;
}
bool Card::operator<=(const Card& rhs) const {
	return !operator>(rhs);
}
bool Card::operator>(const Card& rhs) const {
	return rank > rhs.rank;
}
bool Card::operator>=(const Card& rhs) const {
	return !operator<(rhs);
}

void Card::createCardName ( ) {
	switch (rank) {
		case TWO:
			cardName += "2";
			break;
		case THREE:
			cardName += "3";
			break;
		case FOUR:
			cardName += "4";
			break;
		case FIVE:
			cardName += "5";
			break;
		case SIX:
			cardName += "6";
			break;
		case SEVEN:
			cardName += "7";
			break;
		case EIGHT:
			cardName += "8";
			break;
		case NINE:
			cardName += "9";
			break;
		case TEN:
			cardName += "10";
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
	cardName += " ";
	switch (suit) {
		case CLUB:
			cardName += '\6';
			break;
		case DIAMOND:
			cardName += '\4';
			break;
		case HEART:
			cardName += '\3';
			break;
		case SPADE:
			cardName += '\5';
			break;
		default:
			cardName = "?";
			break;
	}
}

ostream& operator<<(ostream& output, const Card& currentCard) {
	return output << currentCard.cardName;
}