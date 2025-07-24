// farkle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Player.h"

int main()
{
	// Initialize Players
	// Prompt user for player names or to press q to stop entering names
	// There must be at least 2 players to start the game
	std::vector<Player> players;
	std::string playerName;
	while (true) {
		std::cout << "Enter player name (or 'q' to finish): ";
		std::getline(std::cin, playerName);
		if (playerName == "q" || playerName.empty()) {
			if (players.size() < 2) {
				std::cout << "At least 2 players are required to start the game." << std::endl;
			} else {
				break; // Exit loop if at least 2 players
			}
		} else {
			players.emplace_back(playerName); // Add new player
		}
	}
    
	// Game loop
	while (true) {
		for (Player& player : players) {
			player.beginTurn(); // Each player takes a turn
			// Check if the player has won
			if (player.getScore() >= 10000) {
				std::cout << player.getName() << " wins with a score of " << player.getScore() << "!" << std::endl;
				return 0; // End the game
			}
		}
	}
}