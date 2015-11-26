//
// Created by Evan Almonte on 10/29/2015.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Deck.hpp"

using std::cout;

int main ( ) {
	srand (static_cast<unsigned int>(time (NULL)));
	Deck original;
	cout << "---------Before Shuffle---------\n";
	cout << original;
	original.shuffle ( );
	cout << "\n---------After Shuffle---------\n";
	cout << original;
	return 0;
}