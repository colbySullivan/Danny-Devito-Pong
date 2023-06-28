#include <iostream>
#include "Game.h"

//using namespace sf;

int main()
{
	//Init Game engine
	Game game;

	//Game loop
	while (game.running()){
		game.rungame();
	}

	//End of application
	return 0;
}