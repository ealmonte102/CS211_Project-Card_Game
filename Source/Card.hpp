#ifndef CARD_HPP
#define CARD_HPP

#include <iosfwd>
#include <string>

class Card {
public:
	enum Suits {
		CLUB, DIAMOND, HEART, SPADE,
	};
	enum Ranks {
		TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
		JACK, QUEEN, KING, ACE
	};

	Card ( );

	Card (int n);

	Card (Suits s, Ranks r);

	Card (Suits s, Ranks r, int v);

	Suits getSuit ( ) const;

	Ranks getRank ( ) const;

	int getValue ( ) const;

	int compareBySuit (const Card& other) const;

	int compareByRank (const Card& other) const;

	int compareByValue (const Card& other) const;

	friend std::ostream& operator<<(std::ostream& output, const Card& currentCard);

	bool operator==(const Card& rhs) const;

	bool operator<(const Card& rhs) const;

	bool operator<=(const Card& rhs) const;

	bool operator>(const Card& rhs) const;

	bool operator>=(const Card& rhs) const;

private:
	void createCardName ( );

	Suits suit;
	Ranks rank;
	int value;
	std::string cardName;
};

#endif