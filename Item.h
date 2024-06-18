#ifndef __H_ITEM__ // INCLUDE GUARD
#define __H_ITEM__

#include <string>
#include <iostream>

/*
 * Header file of Item.cpp; Item is an object with a name, description,
 * number of calories, and weight,
 * Includes constructors and an overloaded stream operator
 * to format the output of an Item object.
 *
 * Author: Breanna Zinky
 * Date: 10/6/2023
 *
 */


class Item {
	public:
		Item(); // Default constructor
		Item(std::string name, std::string description, int calories, float weight); // Parameterized constructor
		
		/* 
		 * Overloaded stream operator, to return a string 
		 * representing the item in a specific format.
		 * Includes the items name, description, calories, and weight.
		 * Used ChatGPT to help determine how this header of an overloaded stream operator should be written.
		 *
		 * Args:
		 * itemString, a reference to an std::ostream object, the output string that the Item will be written to
		 * item, a constant reference to an item object that's being outputted
		 *
		 * Returns:
		 * A reference to an std::ostream object, the output string to be written to
		 */
		friend std::ostream& operator<<(std::ostream& itemString, const Item& item);
	private:
		std::string name;
		std::string description;
		int calories;
		float weight;
		// Make item a friend of Location and Game so Location
		// and Game can access Item's private variables, without getters and setters.
		friend class Location;
		friend class Game;
};

#endif
