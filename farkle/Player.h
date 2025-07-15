// ============================================================================
// File: Die.h
// Description: Represents a die that may be rolled.
// Author: Daniel Pratt
// Date Created: 07/15/2025
// Last Modified: 07/15/2025
// Version: 1.0
// ============================================================================

#include <vector>
#include <string>
#include "Die.h"

#pragma once
class Player
{
private:
	std::string name;  // player's name
	std::vector<Die> rollingDice; // vector of the player's rolling dice
	std::vector<Die> heldDice; // vector of the player's held dice (used for scoring)
	int score; // player's score

public:
	Player(std::string name);

	std::string getName() const;

	int getScore() const;

	void beginTurn();

	void rollDice();

	void holdDie(int atIndex);

	bool canScoreDie() const;

	void scoreDie();

	void displayDice() const;

	// Prompts for the player
	void promptForAction();

	void promptForHoldDie();
};

