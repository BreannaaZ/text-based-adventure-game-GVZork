#include "Item.h"
#include <string>
#include <iostream>

/*
 * Item.cpp is an Item object that
 * has a name, description, calories, and weight.
 * Includes constructors and an overloaded stream
 * operator to format output of an Item object.
 *
 * Author: Breanna Zinky
 * Date: 10/6/2023
 *
 */

// DEFAULT CONSTRUCTOR
Item::Item(){
	name = "N/A";
	description = "N/A";
	calories = 0;
	weight = 0.0f;
} 

// PARAMETERIZED CONSTRUCTOR
Item::Item(std::string name, std::string description, int calories, float weight){
	// Verify that the inputted values are correct; throw an error if not.
	if (name.empty()){
		throw std::invalid_argument("Name of item cannot be empty.");
	}
	if (description.empty()){
		throw std::invalid_argument("Item description cannot be empty.");
	}
	if (calories < 0 || calories > 1000){
		throw std::invalid_argument("Calories must be between 0 and 1000.");
	}
	// Verify that calories is an integer.
	if (calories != (int)calories){
		throw std::invalid_argument("Calories must be an integer.");
	}
	if (weight < 0 || weight > 500){
		throw std::invalid_argument("Weight must be between 0 and 500 lbs.");
	}
	// Verify that weight is a float.
	if (weight != (float)weight){
		throw std::invalid_argument("Weight must be a float.");
	}
	
	// Set values
	this->name = name;
	this->description = description;
	this->calories = calories;
	this->weight = weight;	
}

// OVERLOADED STREAM OPERATOR - FUNCTION HEADER CAME FROM CHATGPT
std::ostream& operator<<(std::ostream& itemString, const Item& item) {
	itemString << item.name << " (" << item.calories << " calories) - " << item.weight << " lb - " << item.description << std::endl;
	return itemString;
}

