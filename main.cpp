#include <iostream>
#include "NPC.h"
#include "Item.h"
#include "Location.h"
#include "Game.h"

/*
 * Main method to run the GVZork game!
 *
 * Author: Breanna Zinky
 * Date: 10/6/2023
 *
 */

int main(int argc, char** argv){
	// Create the game instance
	Game newGame;
	// Run the play method (core game loop) on the game instance
	newGame.play();

	std::cout << "\nThanks for playing!\n";
	return 0;
}
