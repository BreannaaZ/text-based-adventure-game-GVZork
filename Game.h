#ifndef __GAME_H__ // INCLUDE GUARD
#define __GAME_H__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>

#include "Item.h"
#include "NPC.h"
#include "Location.h"

/*
 * Header for Game.cpp. Game has the values for
 * the current game and player- a map of commands, a vector of items
 * in the player's inventory, the player's weight, a vector
 * of all the locations in this world, an index for this vector
 * representing the current location, the amount of calories left to win,
 * an in progress boolean, amount of coins the user has, and a vector holding
 * items in the shops.
 * Includes constructor, methods to create the world, set up the commands map,
 * get a random number for getting a random location, a play method for the main
 * game loop, and multiple command methods such as go, talk, give, etc. to perform
 * actions and interact with the game world.
 *
 * Author: Breanna Zinky
 * Date: 10/6/2023
 */

class Game{
	private:
		// Map of user entered strings to refer to aliases of functions to be called-
		// so user can input a command and have that method called without a bunch of if statements.
		// Used ChatGPT to help determine what type to use for the function aliases.
		std::map<std::string, std::function<void(std::vector<std::string> target)>> commands; 
		std::vector<Item> items; // Items the player currently has in inventory
		int weight; // Current weight the player is carrying
		std::vector<Location> worldLocations; // Locations that exist in the world
		int currentLocation; // Index for worldLocations vector to represent the current location
		int winningCalories; // The amount of calories the elf needs before it will save the campus (win condition)
		bool inProgress; // Boolean that stores whether the game is still in progress
		int coins; // Added coins variable for some extra fun commands. You can use coins to buy food from shop-keepers
		std::vector<Item> shopItems; // Added shop items vector for some extra fun commands. Holds some food items you can buy
		// Adding Location as a friend so Location can access game's private variables if needed
		// without getters and setters
		friend class Location;
	public:
		/*
		 * Default constructor
		 * Sets up the commands vector, creates the world,
		 * sets up the world locations vector, sets the winning
		 * calories value, and sets the other attributes (weight, coins,
		 * etc.) to 0. Sets inProgress to true, and gets a random location
		 * to start.
		 */
		Game(); 
		/*
		 * create_world creates all the locations, items, and NPCs in the game.
		 * Adds the locations to a vector of all the world's locations.
		 * 
		 * Returns:
		 * A vector of all the world locations.
		 */
		std::vector<Location> create_world();
		/*
		 * setup_commands creates the map of possible
		 * user inputs (ex. give, go, etc.) and the methods they refer to.
		 * Used ChatGPT to help determine what type to use for the values
		 * in the map, the function aliases.
		 * 
		 * Returns:
		 * The map of strings and the function aliases they refer to.
		 */
		std::map<std::string, std::function<void(std::vector<std::string> target)>> setup_commands();
		/*
		 * random_location generates a random number within the number of
		 * locations in the world. This can be used to get a random location
		 * from the world.
		 * Used ChatGPT for the code inside this method and for the functions 
		 * to generate a random number in the specified range.
		 *
		 * Returns:
		 * A random integer between 0 and the amount of locations in the world.
		 * Can be used as an index in the worldLocations vector to select a random location.
		 */
		int random_location();
		/*
		 * play is the core game loop. 
		 * Prints a message describing the game,
		 * then loops while the game is in progress.
		 * Accepts user input for commands each loop.
		 * Splits the user's input up into a command and
		 * target.
		 * Calls the command and passes it the target.
		 */
		void play();
		/*
		 * show_help prints the current time, a help message,
		 * and all of the possible user inputs
		 * for commands (actions the player can make)
		 * from the keys in the commands map.
		 *
		 * Args:
		 * A vector of the user's inputted words
		 * representing the target of the command.
		 */
		void show_help(std::vector<std::string> target);
		/*
		 * talk allows you to talk to the targetted NPC.
		 * Checks if the provided NPC is in the current room,
		 * and if so, calls the NPC's get_message() method and prints
		 * it out.
		 *
		 * Args:
		 * A vector of the user's inputted words
		 * representing the target of the command.
		 */
		void talk(std::vector<std::string> target);
		/*
		 * meet prints out a description of the targetted NPC,
		 * if they exist in the room.
		 *
		 * Args:
		 * A vector of the user's inputted words
		 * representing the target of the command.
		 */
		void meet(std::vector<std::string> target);
		/*
		 * take checks if the target item is in the room,
		 * and if so removes it from the rooms inventory and
		 * adds it to the player's inventory.
		 * It also adds the weight of the item to the player's weight.
		 *
		 * Args:
		 * A vector of the user's inputted words
		 * representing the target of the command.
		 */
		void take(std::vector<std::string> target);
		/*
		 * give removes the targetted item and item's weight from the user's inventory,
		 * if it exists, and adds it to the current location's inventory.
		 * Also checks if the current location is the woods; if it is, checks if the item is edible,
		 * if so- removes the calorie count from the amount left to win, and checks for a win condition.
		 * If the item is not edible, the player is teleported to a random location by calling random_location().
		 *
		 * Args:
		 * A vector of the user's inputted words
		 * representing the target of the command.
		 */
		void give(std::vector<std::string> target); 
		/*
		 * go sets the current location to visited and then
		 * changes your current location to be the one in the targetted
		 * direction, if it exists.
		 *
		 * Args:
		 * A vector of the user's inputted words
		 * representing the target of the command.
		 */
		void go(std::vector<std::string> target);
		/*
		 * show_items prints all items the player is carrying
		 * as well as the amount of coins and current 
		 * inventory weight.
		 *
		 * Args:
		 * A vector of the user's inputted words
		 * representing the target of the command.
		 */
		void show_items(std::vector<std::string> target);
		/*
		 * look prints the current location,
		 * which from the overloaded location stream operator
		 * includes the Items and NPCs in the room,
		 * as well as neighboring locations and directions.
		 *
		 * Args:
		 * A vector of the user's inputted words
		 * representing the target of the command.
		 */
		void look(std::vector<std::string> target);
		/*
		 * Quit allows the user to end the game.
		 * Prints a failure message and sets in progress to false,
		 * so the game ends.
		 *
		 * Args:
		 * A vector of the user's inputted words
		 * representing the target of the command.
		 */
		void quit(std::vector<std::string> target); 
		/*
		 * buy allows the user to buy a random food item from the targetted shopkeeper
		 * (the Pod Store employee or Vending Machine in Mackinac hall).
		 * Takes 25 coins from the player's inventory and gives
		 * one of the food items from the shopItems vector to the
		 * player's inventory, while removing it from shopItems.
		 *
		 * Args:
		 * A vector of the user's inputted words
		 * representing the target of the command.
		 */
		void buy(std::vector<std::string> target); 
		/*
		 * steal allows the player to attempt to pick-pocket
		 * the targetted NPC for coins. It has a 50% chance of success-
		 * if it succeeds, the player is given a random amount of coins,
		 * if it fails, the user is caught and teleported to the
		 * Campus Security location.
		 * Uses random_location() method for random number/chance generation.
		 *
		 * Args:
		 * A vector of the user's inputted words
		 * representing the target of the command.
		 */
		void steal(std::vector<std::string> target); 
};

#endif
