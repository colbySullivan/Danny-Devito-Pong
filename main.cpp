#include <iostream>
#include "Game.hpp"
#include "Game.cpp"

int main(){
	//Init Game engine
	Game game;

	//Game loop
	while (game.running()){
		game.rungame();
	}

	//End of application
	return 0;
}