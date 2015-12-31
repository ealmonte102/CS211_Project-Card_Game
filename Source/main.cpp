//
// Created by Evan Almonte on 10/29/2015.
//

#include "GoFishGame.hpp"
#include <cstdlib>
#include <ctime>

int main ( ) {
	srand (static_cast<unsigned int>(time (nullptr)));
	GoFishGame* aGame = new GoFishGame(2);
	aGame->play ( );
	return 0;
}