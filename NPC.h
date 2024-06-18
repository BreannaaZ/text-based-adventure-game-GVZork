#ifndef __NPC_H__ // INCLUDE GUARD
#define __NPC_H__

#include <iostream>
#include <vector>
#include <string>

/*
 * Header file of NPC.cpp, an NPC object
 * that has a name, description, message number,
 * vector of messages, and robbed attribute.
 * Includes constructors, functions to get the
 * current message from the NPC, add a message to
 * the NPC's messages, and an overloaded stream operator
 * to format the output of an NPC object,
 *
 * Author: Breanna Zinky
 * Date: 10/6/2023
 *
 */

class NPC {
	private:
		std::string name;
		std::string description;
		int messageNum; // Index for what message the NPC is on
		std::vector<std::string> messages; // Vector of all of the NPC's messages
		bool robbed; // Extra variable to store if a NPC has been stolen from yet or not (can only steal from each NPC once).
			     // This is used for the added "steal" command!
		// Making NPC a friend of Location and Game so they can access NPC's private variables
		// without getters and setters.
		friend class Location;
		friend class Game;
	public:
		NPC(); // Default constructor
		NPC(std::string name, std::string description);// Parameterized constructor					       
		/*
		 * getCurrentMessage() returns the current message from the NPC's
		 * messages vector and updates the message number,
		 * allowing you to talk to the NPC and cycle through their messages. 
		 * Returns:
		 * A string representing the current message to be displayed.
		 */
		std::string getCurrentMessage();
		/*
		 * addMessage adds a message to NPC's message vector 
		 * from the back.
		 * Args:
		 * A string representing the message to be added to the NPC's
		 * dialogues.
		 *
		 *
		 */
		void addMessage(std::string message);
		/* 
		 * Overloaded stream operator to return a string
		 * representing the NPC in a specific format.
		 * Includes the name of the NPC. 
		 * Used ChatGPT to determine how the header of an 
		 * overloaded stream operator should be written.
		 * 
		 * Args:
		 * NPCString, a reference to the output stream to be written to
		 * npc, a constant reference to an NPC object to be outputted
		 *
		 * Returns:
		 * A reference to an std::ostream object, the output stream to be written to
		 */ 
		friend std::ostream& operator<<(std::ostream& NPCString, const NPC& npc);
};


#endif
