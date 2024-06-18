#include "NPC.h"
#include <iostream>
#include <string>
#include <vector>

// Default constructor
NPC::NPC(){
	name = "Unnamed";
	description = "They are a mystery...";
	messageNum = 0;
	robbed = false;
	messages.push_back("Where am I? Who am I? What am I?\n");
	messages.push_back("The unnamed NPC gazes confusedly into the distance.\n");
}

// Parameterized constructor
NPC::NPC(std::string name, std::string description){
	// Verify that name and description aren't empty
	if (name.empty()){
		throw std::invalid_argument("NPC name cannot be empty.");
	}
	if (description.empty()){
		throw std::invalid_argument("NPC description cannot be empty.");
	}

	// Set name and description
	this->name = name;
	this->description = description;
	messageNum = 0;
	robbed = false;
}

// Function to get current message and increase message count by 1 (or reset to 0)
std::string NPC::getCurrentMessage(){
	std::string currentMessage = messages.at(messageNum); // Get the message from the current index
	// If the current message is not the last in the vector, increase it to the next, otherwise reset it back to 0.
	if (messageNum < (messages.size() - 1)){
	messageNum++;
	} else messageNum = 0;
	return currentMessage;
}

// Method to add message to NPC's message vector
void NPC::addMessage(std::string message){
	messages.push_back(message);
}

// Overloaded stream operator to return the name of the NPC. Used ChatGPT to help with how this header should be written.
std::ostream& operator<<(std::ostream& NPCString, const NPC& npc){
	NPCString << npc.name << "\n";
	return NPCString;
}
