#ifndef __LOCATION_H__ // INCLUDE GUARD
#define __LOCATION_H__

#include <vector>
#include <map>
#include "Item.h"
#include "NPC.h"
#include <functional> // For reference_wrapper
#include <iostream>
#include <string>

/*
 * Header file for Location.cpp
 * Location is an object with a name, description,
 * attribute to represent if the location has been visited,
 * vector of NPCs in the room, vector of Items in the room,
 * and a map of directions to other neighboring locations.
 * Includes constructors, a method to add a location into the
 * neighbors map, a method to add an NPC to the room, a method
 * to add an item to the room, a method to get the map of neighbors,
 * and an overloaded stream operator to format a Location nicely.
 *
 * Author: Breanna Zinky
 * Date: 10/6/2023
 */

class Location{
	private:
		std::string name;
		std::string description;
		bool alreadyVisited; // Holds whether or not the location has already been visited
		std::vector<NPC> locationNPCs; // Vector of NPCs in the location
		std::vector<Item> locationItems; // Vector of Items in the location
		// Map that holds directions to neighboring locations. Used references
		// since the locations are changing, and using just copies won't reflect these changes.
		// Used reference_wrapper to be able to have a reference in a collection.
		std::map<std::string, std::reference_wrapper<Location> > neighborsMap;
		// Friend of Game so Game can access location's private attributes without
		// getters and setters.
		friend class Game;
	public:
		// Default constructor
		Location();
		// Parameterized constructor
		Location(std::string name, std::string description);
		/*
		 * add_location adds the location into the map with the provided direction string.
		 * 
		 * Args:
		 * A string representing the direction, the key in the map
		 * A Location object representing the neighboring location
		 *
		 */
		void add_location(std::string direction, Location location);
		/*
		 * add_npc adds an NPC to the back of the location's vector
		 * of NPCs in the room
		 * 
		 * Args: 
		 * an NPC object to be added
		 */
		void add_npc(NPC npc);
		/*
		 * add_item adds an Item to the back of the location's
		 * vector of Items in the room.
		 * 
		 * Args:
		 * An Item object to be added
		 */
		void add_item(Item item);
		/*
		 * get_neighbors gets the map of directions
		 * and neighboring locations.
		 * 
		 * Returns:
		 * The map of directions and neighboring locations.
		 */ 
		std::map<std::string, std::reference_wrapper<Location> > get_neighbors();
		/*
		 * Overloaded stream operator to return a string
		 * representing the Location in a specific format.
		 * Includes the name and description of the Location,
		 * a list of the Items and NPCs in the room, and the neighboring
		 * locations and directions.
		 * Used ChatGPT to determine how the header of an
		 * overloaded stream operator should be written.
		 * Args:
		 * locationString, a reference to the output stream to be written to
		 * location, a constant reference to a location object to be outputted
		 *
		 * Returns:
		 * A reference to an std::ostream object, the output stream to be written to       
		 */
		friend std::ostream& operator<<(std::ostream& locationString, const Location& location);
};

#endif
