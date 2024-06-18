#include "Game.h"
#include <iostream>
#include <random> // To generate random number 
#include <boost/algorithm/string.hpp> // For splitting user command string words
#include <ctime> // For date and time stamp
#include <functional>
#include <iterator>
#include <algorithm>

/*
 * Game holds all the locations in the world,
 * the commands map, amount of calories
 * left to win, in progress status, and the player's
 * current location, weight, inventory items,
 * and coins.
 * It includes methods to create the world (all the locations, 
 * NPCs, and Items), set up the commands, get a random location,
 * play which is the core game loop to take user input for commands,
 * and multiple command methods such as talk, go, etc., for the player
 * to interact with the game world,
 * 
 * Author: Breanna Zinky
 * Date: 10/6/2023
 */

// Default Constructor
Game::Game(){
	// Set the commands map equal to the return call from setup_commands().
	commands = Game::setup_commands();
	// Call the create_world method. This method will also set the map/vectors for locations, items, and NPCs.
	worldLocations = create_world();
	// Set default values for all other variables.
	weight = 0;
	winningCalories = 500;
	inProgress = true;
	coins = 0;
	// Set the current location to a random location from the random_location method.
	currentLocation = random_location();
}

// Create_world method that sets all the locations, items, and npcs in the world.
std::vector<Location> Game::create_world(){
	// Declare all locations
	Location woods("The Woods", "The woods behind the library. It's strangely quiet and serene...");
	Location mackinacHall("Mackinac Hall", "A large building with many classrooms and offices. You've never seen it this empty before...");
	Location podStore("The Pod Store", "A small store in Mackinac Hall with snacks and drinks. There are multiple places to sit.");
	Location gym("The gym", "There's plenty of exercise equipment. It kind of smells, and it looks like some people forgot their drinks here.");
	Location library("Mary Idema Pew Library", "There's plenty of areas to lounge around and study. There's a few students still studying...");
	Location parkingLot("A parking lot", "There's a strange lack of cars today. Normally parking is MUCH worse...");
	Location campusSecurity("Campus Security Building", "You would rather not spend too much time in here.");
	Location kirkhoffCenter("Kirkhoff Center", "Theres multiple restaurants and places to sit and eat. There's plenty of half-eaten food left lying around...");
	Location dormitory("One of the dormitories.", "Some students left their doors open. Maybe you can loot their dorms?");
	//////////////////// Location 1 - Woods ///////////////////////
	// Create items
	Item leaves("Leaves", "A mix of green and brown leaves. Could an elf eat this?", 0, 3.5f);
	Item sticks("Sticks", "Just some sticks... You have no use for them.", 0, 5.0f);
	Item acorns("Acorns", "Some fallens acorns. Are they edible like this? You can't recall.", 0, 4.0f);
	Item berries("Berries", "Some red berries on a bush. Let's hope they aren't poisonous...", 35, 2.5f);
	// Add items to location
	woods.add_item(leaves);
	woods.add_item(sticks);
	woods.add_item(acorns);
	woods.add_item(berries);
	// Create NPCs
	NPC Elf("Elf", "A strange and magical looking being. You can tell they are powerful. Perhaps they can help save the campus?");
	Elf.addMessage("Who am I? You don't know me? Well, I'm just the most powerful elf in Allendale...");
	Elf.addMessage("Your campus is in trouble? And you want my help? Sorry, I'm too hungry right now. I have no energy to do anything.");
	Elf.addMessage("You're that desperate? Bring me food and I might consider helping. I'm famished.");
	Elf.addMessage("How much food? I usually eat around 500 calories. That would do.");
	Elf.addMessage("Their stomach growls loudly. They look embarrased.");
	// Add NPC to location
	woods.add_npc(Elf);
	///////////////// Location 2 - Mackinac Hall ////////////////////////
	// Create items (Don't add them to the location because they must be obtained
	// through purchase from the vending machine).
	Item smallChips("Chips", "A bag of plain potato chips. It's the worst flavor...", 40, 4.0f);
	Item smallCandy("Candy", "A chocolate bar. You're tempted to eat it.", 25, 2.0f);
	Item energyDrink("Energy drink", "An essential item for college students. Its packed full of caffeine. Hopefully the Elf doesn't have heart issues...", 10, 1.5f);
	// Create NPCs
	NPC Professor("Professor", "You haven't taken any of their classes.");
	Professor.addMessage("Where are all the students at? No one showed up for my class...");
	Professor.addMessage("What was I teaching? Well, I was giving a lecture on... (he rambles on for 20 minutes).");
	Professor.addMessage("Interesting stuff, huh? Would you like to hear more?... No? Okay.");
	NPC vendingMachine("Vending machine", "It's a vending machine with plenty of snacks and drinks. If you had money you could buy some.");
	vendingMachine.addMessage("The vending machine sits there silently.");
	vendingMachine.addMessage("It doesn't talk. Maybe you should give it money *cough* 25 coins *cough* and buy something?");
	// Add NPCs to location
	mackinacHall.add_npc(Professor);
	mackinacHall.add_npc(vendingMachine);
	/////////////// Location 3 - Pod Store ////////////////////////
	// Create items (Again, not adding some to the location since they must be bought through employee)
	Item sandwich("Sandwich", "A turkey, cheese, lettuce, and mayo sandwich. It doesn't look bad.", 50, 5);
	Item water("Water", "A water bottle. It has 0 calories, but maybe the Elf is thirsty?", 0, 4.0f);
	Item candy("Large candy bar", "A large caramel chocolate candy bar. Yum!", 45, 4.0f);
	Item chips("Large bag of chips", "A large bag of spicy chips. They taste good, but beware of heartburn!", 45, 5.0f);
	// Add freely available item to location
	podStore.add_item(water);
	// Create NPCs
	NPC Employee("Employee", "It's a store employee. You could purchase some items through them.");
	Employee.addMessage("I shouldn't have to be working right now...");
	Employee.addMessage("Want to buy something? For 25 coins I'll give you something tasty.");
	Employee.addMessage("Why am I using coins instead of normal cash? This is an adventure game... don't question it.");
	NPC Student1("Random Student", "It's a random student eating a sandwich. They look carefree.");
	Student1.addMessage("Just aced my exams. Too easy!");
	// Add NPCs to location
	podStore.add_npc(Employee);
	podStore.add_npc(Student1);
	////////////////// Location 4 - Gym //////////////////////
	// Create items
	Item proteinShake("Protein shake", "It doesn't look very appealing... How long has it been left here?", 50, 5.0f);
	Item gatorade("Gatorade", "An open gatorade. Someone drank out of this... yuck.", 25, 3.0f);
	Item weights("A single weight", "Do you really need this? It would likely just weigh you down.", 0, 15.0f);
	// Add items to location
	gym.add_item(proteinShake);
	gym.add_item(gatorade);
	gym.add_item(weights);
	// Create NPCs
	NPC rat("Rat", "It's a large rat!!!");
	rat.addMessage("*The rat squeaks at you.*");
	rat.addMessage("(Need some cash? Try using *steal* on an NPC. Just don't get caught!)... *Wait, did the rat just speak?*");
	NPC athlete("Athlete", "Some athlete exercising. Go Lakers!");
	athlete.addMessage("I'm busy making gains right now.");
	// Add NPCs to location
	gym.add_npc(rat);
	gym.add_npc(athlete);
	/////////////// Location 5 - Library ////////////////////////
	// Create items
	Item book("Book", "A mystery novel. Seems interesting!", 0, 5.0f);
	Item notebook("Notebook", "A used notebook. Looks like it was used for a math course.", 0, 4.0f);
	Item laptop("Laptop", "Someone left their laptop here! You should probably leave it alone.", 0, 8.0f);
	Item coffee("Coffee", "An essential drink for college students. You've drank it a lot before exams.", 35, 3.0f);
	// Add items to location
	library.add_item(book);
	library.add_item(notebook);
	library.add_item(laptop);
	library.add_item(coffee);
	// Create NPCs
	NPC librarian("Librarian", "You could ask them for help finding things.");
	librarian.addMessage("Hi, can I help you?");
	librarian.addMessage("You're on a quest to save the campus and need to collect food? Well, food isn't allowed in here. Try Kirkhoff Hall, you are bound to find food there.");
	librarian.addMessage("If you have money, maybe you can buy food from stores and vending machines too.");
	NPC sadStudent("A sad student", "Looks like they may have been crying. Maybe they flunked an exam?");
	sadStudent.addMessage("MY LIFE IS OVER! I just failed two exams and missed a project deadline.");
	sadStudent.addMessage("Thanks, but I'm okay... I probably should've studied.");
	NPC stressedStudent("A stressed student", "They sit in front of a laptop, three open notebooks, and two energy drinks. They must be cramming for an exam. Good luck!");
	stressedStudent.addMessage("Shhhh! I'm trying to study!");
	stressedStudent.addMessage("This is my third energy drink today. I think I'm gonna puke. But I've never been more focused.");
	stressedStudent.addMessage("I'm so gonna fail.. - no, wait, I'll just pull an allnighter and learn it all.");
	// Add NPCs to location
	library.add_npc(librarian);
	library.add_npc(sadStudent);
	library.add_npc(stressedStudent);
	/////////////// Location 6 - Parking Lot ////////////////////
	// Create items
	Item carKeys("Car keys", "Someone must've dropped them. That sucks.", 0, 2.0f);
	Item wallet("Wallet", "It was dropped near the car keys. That's some serious bad luck!", 0, 3.0f);
	Item granolaBar("Granola bar", "A crushed granola bar lying on the ground. You wouldn't eat it, but the Elf doesn't need to know where it came from.", 35, 3.0f);
	// Add items to location
	parkingLot.add_item(carKeys);
	parkingLot.add_item(wallet);
	parkingLot.add_item(granolaBar);
	// Create and add NPCs to location
	NPC squirrel("Squirrel", "Aw, how cute! A friendly looking brown squirrel. It's eating something.");
	squirrel.addMessage("*The squirrel stands up intimidatingly as if telling you to back up.*");
	NPC badDriver("Driver", "It's a student driving. Seems like they are struggling to park.");
	badDriver.addMessage("WATCH OUT! I'M DRIVING HERE!");
	badDriver.addMessage("This is good enough, right?");
	badDriver.addMessage("*The driver hits the car next to them with their door... They ignore it.*");
	parkingLot.add_npc(squirrel);
	parkingLot.add_npc(badDriver);
	/////////////// Location 7 - Campus Security ////////////////////////
	// Create items
	Item donuts("Box of donuts", "Oooh, a box of chocolate and powdered donuts. That's sort of cliche...", 50, 10.0f);
	campusSecurity.add_item(donuts);
	// Create and add NPCs and dialogue
	NPC securityGuard("Security guard", "A security guard. He looks stern.");
	securityGuard.addMessage("Don't do anything illegal. I'm watching you.");
	securityGuard.addMessage("You DEFINITELY shouldn't try using *steal* on someone. That would get you in real trouble.");
	NPC angryStudent("Angry student", "An angry student. Looks like they got in trouble.");
	angryStudent.addMessage("This is so unfair!");
	angryStudent.addMessage("I did nothing wrong. I'm calling my lawyer.");
	campusSecurity.add_npc(securityGuard);
	campusSecurity.add_npc(angryStudent);
	/////////////// Location 8 - Kirkhoff Center ///////////////////////
	// Create and add items
	Item subwaySub("Subway sub", "A footlong oven-roasted turkey sub from subway, yum!", 60, 5.0f);
	Item chickenBowl("Panda Express chicken and rice bowl", "A partly-eaten bowl of chicken and rice from Panda Express. It still looks appetizing.", 60, 5.0f);
	Item mysteryFood("Dining hall mystery food", "You can't tell what this is... it doesn't smell the best.", 0, 4.0f);
	Item napkins("Napkins", "Some napkins. Nothing special.", 0, 2.0f);
	kirkhoffCenter.add_item(subwaySub);
	kirkhoffCenter.add_item(chickenBowl);
	kirkhoffCenter.add_item(mysteryFood);
	kirkhoffCenter.add_item(napkins);
	// Create and add NPC
	NPC janitor("Janitor", "They're cleaning up after the mess students left.");
	janitor.addMessage("*whistling*");
	kirkhoffCenter.add_npc(janitor);
	////////////// Location 9 - Dormitory //////////////////////////
	// Create and add items
	Item chickenStrips("Half-eaten burnt chicken strips", "A popular food for college students. Looks like they air-fried it for too long.", 35, 3.0f);
	Item cheetos("Flaming Hot Cheetos", "A bag of flaming hot cheetos. It's open and they smell stale.", 40, 3.0f);
	dormitory.add_item(chickenStrips);
	dormitory.add_item(cheetos);
	//////////////// Shop Items /////////////////////////
	// Some items held in a vector that you can buy using the added buy command
	Item soda("Soda", "Packed with sugar... bad for your teeth... but so good!", 25, 3.0f);
	Item goldenApple("Golden apple", "A real golden apple?! But you bought it for so cheap!", 100, 5.0f);
	Item steak("Steak", "They sell steak here? It does look good though...", 50, 4.0f);
	Item bread("Bread", "A small packaged bread roll.", 35, 3.0f);
	Item MRE("MRE", "A precooked and prepackaged meal. This would be good in an apocalypse.", 75, 6.0f);
	shopItems.push_back(soda);
	shopItems.push_back(goldenApple);
	shopItems.push_back(steak);
	shopItems.push_back(bread);
	shopItems.push_back(MRE);
	///////////////////// Add Locations to World //////////////////////////////
	std::vector<Location> allLocations; // Vector to add the locations to
	// Add the locations
	allLocations.push_back(woods); // 0
	allLocations.push_back(mackinacHall); // 1
	allLocations.push_back(podStore); // 2
	allLocations.push_back(gym); // 3
	allLocations.push_back(library); // 4
	allLocations.push_back(parkingLot); // 5
	allLocations.push_back(campusSecurity); // 6
	allLocations.push_back(kirkhoffCenter); // 7
	allLocations.push_back(dormitory); // 8
	// Add locations neighbors
	// Adding them this way fixed errors from adding the locations in other ways,
	// ex. from calling add_location
	allLocations[0].neighborsMap.insert_or_assign("West", allLocations[4]);
	allLocations[1].neighborsMap.insert_or_assign("West", allLocations[6]);
	allLocations[1].neighborsMap.insert_or_assign("North", allLocations[2]);
	allLocations[1].neighborsMap.insert_or_assign("South", allLocations[3]);
	allLocations[2].neighborsMap.insert_or_assign("North", allLocations[8]);
	allLocations[2].neighborsMap.insert_or_assign("South", allLocations[1]);
	allLocations[3].neighborsMap.insert_or_assign("North", allLocations[1]);
	allLocations[3].neighborsMap.insert_or_assign("West", allLocations[5]);
	allLocations[4].neighborsMap.insert_or_assign("West", allLocations[7]);
	allLocations[4].neighborsMap.insert_or_assign("East", allLocations[0]);
	allLocations[4].neighborsMap.insert_or_assign("South", allLocations[6]);
	allLocations[5].neighborsMap.insert_or_assign("North", allLocations[6]);
	allLocations[5].neighborsMap.insert_or_assign("East", allLocations[3]);
	allLocations[6].neighborsMap.insert_or_assign("East", allLocations[1]);
	allLocations[6].neighborsMap.insert_or_assign("South", allLocations[5]);
	allLocations[6].neighborsMap.insert_or_assign("North", allLocations[4]);
	allLocations[7].neighborsMap.insert_or_assign("East", allLocations[4]);
	allLocations[8].neighborsMap.insert_or_assign("South", allLocations[2]);

	return allLocations;
}

// Creates a new map. Keys = strings such as talk, give, go, etc.
// Values of the map = names of functions to be called for each of those commands.
std::map<std::string, std::function<void(std::vector<std::string> target)> > Game::setup_commands(){
	// Add the function aliases to the map with the text input to refer to them
	// Multiple keys refer to the same function to account for synonyms/other similar commands the player
	// may try typing.
	// Used ChatGPT to help figure out how to set the functions.
	commands["help"] = [this](std::vector<std::string> target) { this->show_help(target); };
	commands["?"] = [this](std::vector<std::string> target) { this->show_help(target); };
	commands["talk"] = [this](std::vector<std::string> target) { this->talk(target); };
	commands["chat"] = [this](std::vector<std::string> target) { this->talk(target); };
	commands["meet"] = [this](std::vector<std::string> target) { this->meet(target); };
	commands["greet"] = [this](std::vector<std::string> target) { this->meet(target); };
	commands["take"] = [this](std::vector<std::string> target) { this->take(target); };
	commands["give"] = [this](std::vector<std::string> target) { this->give(target); };
	commands["go"] = [this](std::vector<std::string> target) { this->go(target); };
	commands["show_items"] = [this](std::vector<std::string> target) { this->show_items(target); };
	commands["inventory"] = [this](std::vector<std::string> target) { this->show_items(target); };
	commands["look"] = [this](std::vector<std::string> target) { this->look(target); };
	commands["quit"] = [this](std::vector<std::string> target) { this->quit(target); };
	commands["buy"] = [this](std::vector<std::string> target) { this->buy(target); };
	commands["steal"] = [this](std::vector<std::string> target) { this->steal(target); };
	commands["rob"] = [this](std::vector<std::string> target) { this->steal(target); };
	commands["pickpocket"] = [this](std::vector<std::string> target) { this->steal(target); };

	return commands;
}

 // Generate a random number within worldLocations vector size,
 // which can then be used as an index to select a random world location
int Game::random_location(){
	// Used AI (chatGPT) for the following lines of code to generate a random number
	std::random_device rd;  // Seed engine with a random value
	std::mt19937 gen(rd()); // Mersenne Twister engine
	// Select random number within the beginning and end of worldLocations vector
	std::uniform_int_distribution<int> dist(0, (worldLocations.size() - 1));
	int randomAccess = dist(gen);
	return randomAccess;
}

// Core game loop, takes user input for commands while in progress
void Game::play(){
	// Print message describing the game
	std::cout << "Welcome to GVZork!\nIn this story-driven, text-based game you can enter various commands to perform actions and interact with your surroundings.\nRight now the campus is in trouble- and it's your job to save it.\nHow do you save the campus? Well, that's up to you to find out- but you can start by talking with the Elf in the forest. Have fun!" << std::endl;	

	// Loop while the game is still in progress
	while (inProgress){
		std::string user_input;
		// In the loop, prompt the user for a command
		std::cout << "\nWhat will you do next: ";
		std::getline(std::cin, user_input);

		// Split the user's input into a vector of words.
		// Refered to cplusplus.com list of libraries to find this function/how to use it
		std::vector<std::string> tokens;
		boost::split(tokens, user_input, boost::is_any_of(" ")); // Split user_input by spaces, add into tokens.
		// Now create variable command to be equal to first element in the vector
		std::string command = tokens[0]; // Make sure this actually sets the string and not to an address
		tokens.erase(tokens.begin()); // Now remove the first element
		
		// Now check the command and call it's method
		auto it = commands.find(command);
		if (it != commands.end()) {
			it->second(tokens);
		} else {
			std::cout << "Invalid command." << std::endl;
		}		
	}
}

// Prints date and time, help message, and all possible commands
void Game::show_help(std::vector<std::string> target){
	// Print out date and time, using std::time from <ctime>. Found through cppreference documentation.
	std::time_t currentTime = std::time(nullptr); // Returns the current calendar time (time since epoch) as a time_t object.
						      // Also stores it in the object pointed to by arg- we can
						      // pass null here since we don't need to store it in any object.
	std::cout << std::asctime(std::localtime(&currentTime)) << std::endl; // asctime converts the time into a nice format
									      // Local time converts the time_t into a local calendar time

	// Print out help message and all commands frm command map's keys
	std::cout << "Confused on how to play? Here are all the commands you can enter: " << std::endl;
	// Print commands from command map's keys
	std::map<std::string, std::function<void(std::vector<std::string> target)> >::iterator it = commands.begin();
	while (it != commands.end()){
	std::cout << it->first << std::endl;
	++it;
	}
	std::cout << "Make sure your format your answers as a one word command and then a single target- ex. take bag of chips\nAlso- make sure your capitalization and spacing matches!" << std::endl; 	
} 

// Quits the game
void Game::quit(std::vector<std::string> target){
	std::cout << "You gave up before reaching the end. Quitting.";
	inProgress = false;
}

// Talk to the target NPC (cycle through their messages)
void Game::talk(std::vector<std::string> target){
	// Check if the provided NPC (target) is in the current room.
	// Join target as a single string
	std::string targetString = boost::algorithm::join(target, " "); // Code to join the vector of words from chatGPT
	bool validTarget = false; // This will be used to print if the user entered an invalid target; used a new
							  // variable for this outside the for loop so the invalid target message will only be printed once.
	// Loop through location's NPC vector to check if the target exists in it
	for (auto j = worldLocations[currentLocation].locationNPCs.begin(); j != worldLocations[currentLocation].locationNPCs.end(); ++j){
		if (targetString == j->name){
			// Call NPC's get_message method and print
			std::cout << j->name << ": " << j->getCurrentMessage() << std::endl;
			validTarget = true;
			} 
		}
	if (!validTarget){
		std::cout << "Invalid target. Make sure to match the spaces, capitalization, and spelling." << std::endl;
	}	
}

// Get the targetted NPC's description
void Game::meet(std::vector<std::string> target){
	// Join target as a single string
	std::string targetString = boost::algorithm::join(target, " "); // Code to join the vector of words from chatGPT
	bool validTarget = false; // This will be used to print if the user entered an invalid target; used a new
							  // variable for this outside the for loop so the invalid target message will only be printed once.
	// Check if the provided NPC exists in the current room
	for (auto j = worldLocations[currentLocation].locationNPCs.begin(); j != worldLocations[currentLocation].locationNPCs.end(); ++j){
			if (targetString == j->name){
				// Call NPC's get_description method and print
				std::cout << j->description << std::endl;
				validTarget = true;
			}
		}
	if (!validTarget){
		std::cout << "Invalid target. Make sure to match the spaces, capitalization, and spelling." << std::endl;
	}
}

// Take the targetted item from the room, adding it to player inventory
void Game::take(std::vector<std::string> target){
	// Join target as a single string
	std::string targetString = boost::algorithm::join(target, " "); // Code to join the vector of words from chatGPT
	bool validTarget = false; // This will be used to print if the user entered an invalid target; used a new
							  // variable for this outside the for loop so the invalid target message will only be printed once.
	// Check if the provided item exists in the current room
	// Using an int instead of iterator here (although it seems more complicated) because using an iterator threw errors when removing the item.
	for (int i = 0; i < worldLocations[currentLocation].locationItems.size(); ++i){
		if (targetString == worldLocations[currentLocation].locationItems[i].name){
			// Add item to user's inventory
			items.push_back(worldLocations[currentLocation].locationItems[i]);
			// Add to the user's weight
			weight += worldLocations[currentLocation].locationItems[i].weight;
			// Remove the item from the room's inventory
			worldLocations[currentLocation].locationItems.erase(worldLocations[currentLocation].locationItems.begin() + i);
			validTarget = true;	
		}	
	}
	if (!validTarget){
		std::cout << "Invalid target. Make sure to match the spaces, capitalization, and spelling." << std::endl;
	}
}

// Give the targetted item from the user's inventory to
// the current location. If you are in the woods, feeds the
// elf and checks for the win condition.
void Game::give(std::vector<std::string> target){	
	// Join target as a single string
	std::string targetString = boost::algorithm::join(target, " "); // Code to join the vector of words from chatGPT
	bool validTarget = false; // Used to print if the user entered an invalid target. Used a new variable
							  // for this outside the for loop so the invalid target message will only display once.	
	// Check if item exists in user's inventory
	for (int i = 0; i < items.size(); ++i){
		if (targetString == items[i].name){
			// Add item to room
			worldLocations[currentLocation].add_item(items[i]);
			// Remove item and weight from player inventory
			items.erase(items.begin() + i);
			weight -= items[i].weight;
			// Check if current location is the woods
			if (worldLocations[currentLocation].name == "The Woods"){
				// Check if item was edible
				if (worldLocations[currentLocation].locationItems.back().calories > 0){
					// Remove the calories from the amount still needed to win
					winningCalories -= worldLocations[currentLocation].locationItems.back().calories;
					// Check for win condition
					if (winningCalories <= 0){
						std::cout << "Congrats! You win." << std::endl;
						inProgress = false;
					} else {
						std::cout << "Elf: I'm still hungry... I could use, say, " << winningCalories << " more calories... Just a rough estimate." << std::endl;
					}
					// If items was edible, erase it from the room as well
					worldLocations[currentLocation].locationItems.pop_back();	
				} else { // If item was not edible, TP player randomly
					std::cout << "Elf: Gah! I can't eat this. Find me real food!\n*The elf waves their wand, and you are teleported away*" << std::endl;
					worldLocations[currentLocation].alreadyVisited = true; // Make sure location is set to visited before being teleported to a new one
					currentLocation = random_location(); // Teleport to random location
				}	
			}
		validTarget = true;
		}
	}
	if (!validTarget){
		std::cout << "Invalid target. Make sure to match the spaces, capitalization, and spelling." << std::endl;	
	}
}

// Travel to a new location at the targetted direction
void Game::go(std::vector<std::string> target){
	// Set current location visited status to true
	worldLocations[currentLocation].alreadyVisited = true;
	// Check if player has over 30 weight
	if (weight > 30){
		std::cout << "Your backpack is too heavy to travel anywhere else; please drop some items if you wish to move on." << std::endl;
		return;
	}
	// Check if provided direction exists in the current location's neighbor map
	// Join target as a single string
	std::string targetString = boost::algorithm::join(target, " "); // Code to join the vector of words from chatGPT
	bool validTarget; // Used to print a message if an invalid target was entered.
					  // Using a new variable here instead of in the for loop so it only prints once.
	// Loop through location's neighbor map (keys for direction- north, east, south, west) and check it to targetString
	int indexNum = 0; 
	for (auto i = worldLocations[currentLocation].neighborsMap.begin(); i != worldLocations[currentLocation].neighborsMap.end(); ++i){
		if (targetString == i->first){
			// Now find what index the next direction is at in worldLocations vector -- code for this loop and inside from chatGPT
			for (indexNum = 0; indexNum < worldLocations.size(); ++indexNum){
				if (&(worldLocations[indexNum]) == &(i->second.get())){
					break;
				}
			}
		validTarget = true;
		}
	}
	if (!validTarget){
	std::cout << "Invalid target. Make sure to match the spaces, capitalization, and spelling." << std::endl;
	return;
	}
        currentLocation = indexNum;	
}

// Print the player's inventory and weight
void Game::show_items(std::vector<std::string> target){
	// Print all items the player is carrying
	std::cout << "You are carrying the following items: " << std::endl;
	for (auto i = items.begin(); i!= items.end(); ++i){
		std::cout << *i;
	}
	// Print out coins amount
	std::cout << "You have " << coins << " coins. Spend them wisely!" << std::endl;
	// Print out current weight
	std::cout << "The current weight you are carrying is: " << weight << std::endl;
}

// Print details about the current location
void Game::look(std::vector<std::string> target){
	std::cout << worldLocations[currentLocation] << std::endl;
}

// Extra command - allows the player to buy a random food item
// with coins from one of the shopkeeper NPCs (pod store employee and vending machine)
void Game::buy(std::vector<std::string> target){
	// Target = specific NPC (vending machine or employee)
	// Join target as a single string
	std::string targetString = boost::algorithm::join(target, " "); // Code to join the vector of words from chatGPT
	bool validTarget = false; // Used to print if the user entered an invalid target
	// Loop through the room's NPCs to check if a valid NPC was targeted
	for (auto i = worldLocations[currentLocation].locationNPCs.begin(); i != worldLocations[currentLocation].locationNPCs.end(); ++i){
		if (targetString == i->name){
			// Return if the NPC isn't one of the ones you can buy from.
			if (i->name != "Vending machine" && i->name != "Employee"){
				std::cout << "They aren't selling anything." << std::endl;
				return;
			}
			// Check that shopItems vector isn't empty (that all items have not been bought already)
			if (shopItems.empty()){
				std::cout << "They have nothing more to sell." << std::endl;
				return;
			}
			// Check that user has enough coins
			if (coins < 25){
				std::cout << "You don't have enough coins. 25 coins a pop." << std::endl;
				return;
			}
			// Remove coins from player's inventory
			coins -= 25;
			// Add the bought item to inventory
			items.push_back(shopItems[0]);
			// Add weight
			weight += shopItems[0].weight;
			// Print message about item bought
			std::cout << "For 25 coins, you bought a: " << shopItems[0].name << std::endl;
			// Remove the item from the shopItem vector
			shopItems.erase(shopItems.begin());
			validTarget = true;
		} 
	}
	if (!validTarget){
	std::cout << "Invalid target. Make sure to match the spaces, capitalization, and spelling." << std::endl;
	}
}

// Extra command - allows the player to pickpocket the 
// targetted NPC for coins; however, comes with a risk of getting caught!
void Game::steal(std::vector<std::string> target){
	// Join target as a single string
	std::string targetString = boost::algorithm::join(target, " ");
	bool validTarget = false; // Used to print if the user entered an invalid target
	// Loop through the room's NPCs to check if a valid NPC was targeted
	for (auto i = worldLocations[currentLocation].locationNPCs.begin(); i != worldLocations[currentLocation].locationNPCs.end(); ++i){
		if (targetString == i->name){
			// Check that the NPC isn't one you cannot steal from (cannot use steal on vending machine, podstore employee, and elf)
			if (i->name == "Vending machine" || i->name == "Employee"){
				std::cout << "You cannot steal from them." << std::endl;
				return;
			}
			// Stealing from the Elf is a bad idea.
			if (i->name == "Elf"){
				std::cout << "Elf: YOU DARE?!?!\n*The Elf strikes you with lightning...* GAME OVER." << std::endl;
				inProgress = false;
				return;
			}
			// Using random_location function to generate a random number between 0 and 9.
			int randomChance = random_location();
			if (randomChance == 2 || randomChance == 5 || randomChance == 7 || randomChance == 0 || randomChance == 1){ // 5/10 - 50% chance of being caught and teleported.
				std::cout << i->name << ": HEY! What do you think you're doing?!?! SECURITY!" << std::endl;
				std::cout << "*Security escorts you away...*" << std::endl;			
				worldLocations[currentLocation].alreadyVisited = true; // Make sure current location is set to visited before changing it
				currentLocation = 6; // index for campus security location
				return;
				}
				// Can't steal from someone twice - check if they've been robbed yet	
				if (i->robbed){
					std::cout << "You already stole from them... how heartless are you?!?!" << std::endl;
					return;
				}	
				// Using the same randomly generated number to decide how many coins to give.
				if (randomChance == 1){ 
					std::cout << "Success! You have stolen 10 coins. Not bad." << std::endl;
					coins += 10;
					i->robbed = true;
				} else if (randomChance == 4 || randomChance == 6 || randomChance == 9){
					std::cout << "Oh... they don't have much. You stole 5 coins." << std::endl;
					coins += 5;
					i->robbed = true;
				} else {
					std::cout << "Score! Their wallet is packed. You stole 15 coins." << std::endl;
					coins += 15;
					i->robbed = true;
				}
		validTarget = true;	
		}
	}
	if (!validTarget){
	std::cout << "Invalid target. Make sure to match the spaces, capitalization, and spelling." << std::endl;
	}
}


