// farkle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Player.h"

int main()
{
    // Seed the random number generator once at the start of the program
    srand(static_cast<unsigned int>(time(0)));

    Player p1 = Player("Daniel");
	Player p2 = Player("Computer");

	std::cout << "Welcome to Farkle!" << std::endl;
	std::cout << "Player 1: " << p1.getName() << std::endl;
	std::cout << "Player 2: " << p2.getName() << std::endl;
	std::cout << "Starting the game..." << std::endl;
	
	// Setup Game Loop
	while (true) {
		p1.beginTurn();
		p2.beginTurn();
	}
    
}