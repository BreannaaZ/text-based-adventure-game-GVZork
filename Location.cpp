#include "Location.h"
#include <iostream>
#include <string>
#include <functional>
#include <vector>

/*
 * A Location object that has a name,
 * description, attribute representing whether
 * the location has been visited, a vector of NPCs
 * in the room, a vector of Items in the room,
 * and a map of directions and neighboring Locations.
 * Includes functions to add a location to the neighbors map,
 * add an item to the room, add an NPC to the room, get
 * the neighbors, and an overloaded stream operator
 * to print out the Location in a specific format.
 *
 * Author: Breanna Zinky
 * Date: 10/6/2023
 */

// Default constructor
Location::Location(){
	name = "The Void";
	description = "An empty pitch black void of nothingness...";
	alreadyVisited = false;
}

// Parameterized constructor
Location::Location(std::string name, std::string description){
	this->name = name;
	this->description = description;
	this->alreadyVisited = false;
}

// Method to add the location into the map with the provided direction string
void Location::add_location(std::string direction, Location location){
	// Raise an exception if the string is blank or the key already exists in the map
	if (direction.empty()){
		throw std::invalid_argument("Direction string cannot be empty");
	}
	if (neighborsMap.count(direction)) { // AI/ChatGPT was used to find the count function to determine if
					     // direction already exists in neighborsMap as a key
		throw std::invalid_argument("This direction is already a key in the map.");
	}
	// neighborsMap[direction] = location does not work. This is because the [] operator of a map requires the 
	// value to be default-constructible. Instead, we can use something else here (found through documentation):
	neighborsMap.insert_or_assign(direction, location);
}

// Method to add an NPC to the locations vector of NPCs from the back
void Location::add_npc(NPC npc){
	locationNPCs.push_back(npc);
}

// Method to add an item to the locations vector of NPCs from the back
void Location::add_item(Item item){
	locationItems.push_back(item);
}

// Method to get the map of neighbors
std::map<std::string, std::reference_wrapper<Location> > Location::get_neighbors(){
	return neighborsMap; 
}

// Overloaded stream operator to print the location with information like name,
// description, items, NPCs, and neighbors
std::ostream& operator<<(std::ostream& locationString, const Location& location){
	locationString << "\n" << location.name << " - " << location.description << std::endl; // name and desc
	if (location.locationNPCs.empty()){
		locationString << "\nYou are alone..." << std::endl;
	} else { 
		locationString << "\nYou see the following NPCs: \n";
		// List the NPCs from NPC vector	
		for (int n = 0; n < location.locationNPCs.size(); n++){
			locationString << " - " << location.locationNPCs.at(n);       
		}
	}
	if (location.locationItems.empty()){
		locationString << "\nThere are no items here." << std::endl;
	} else {
		locationString << "\nYou see the following Items: \n";
		// List the items from item vector
		for (int i = 0; i < location.locationItems.size(); i++){
			locationString << " - " << location.locationItems.at(i);
		}
	}
		// List the neighbor locations 
	locationString << "\nYou can go in the following Directions: ";
		for (auto j = location.neighborsMap.begin(); j != location.neighborsMap.end(); ++j){
			// If location hasn't been visited, do not print the name - print unknown.
			if (!j->second.get().alreadyVisited){
				locationString << "\n - " << j->first << " - " << "Unknown";
			} else {
				locationString << "\n - " << j->first <<  " - " << j->second.get().name << " (Visited) ";
			}
		}
	locationString << std::endl; 
	return locationString;
}


