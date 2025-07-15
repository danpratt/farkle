#include "Player.h"
#include <iostream>
#include <algorithm>

Player::Player(std::string name)
{
	this->name = name;
	score = 0; // Initialize score to 0
}

std::string Player::getName() const
{
	return name;
}

int Player::getScore() const
{
	return score;
}

void Player::beginTurn()
{
	// overwrite rollingDice vector with new dice
	rollingDice = { Die(), Die(), Die(), Die(), Die(), Die() };
	displayDice();
	promptForAction();
}

void Player::rollDice()
{
	for (Die& die : rollingDice) {
		die.roll();
	}
	std::cout << "Rolled dice: ";
	displayDice();
	std::cout << std::endl;
	promptForAction();
}

void Player::holdDie(int atIndex)
{
	if (atIndex < 0 || atIndex >= rollingDice.size()) {
		std::cout << "Invalid index. Cannot hold die." << std::endl;
		return;
	}
	// Move the die from rollingDice to heldDice
	heldDice.push_back(rollingDice[atIndex]);
	rollingDice.erase(rollingDice.begin() + atIndex);
	std::cout << "Held die: " << heldDice.back().displayValue() << std::endl;
	displayDice();
}

bool Player::canScoreDie() const
{
    // Create a copy of rollingDice and sort it
	int counts[6] = { 0 }; // Array to count occurrences of each die value (1-6)
	for (const Die& die : rollingDice) {
		if (die.getValue() >= 1 && die.getValue() <= 6) {
			counts[die.getValue() - 1]++;
		}
	}

	// Check for scoring conditions
	if (counts[0] >= 1) {
		return true; // At least one 1
	}

	if (counts[4] >= 1) {
		return true; // At least one 5
	}

	for (int i = 0; i < 6; ++i) {
		if (counts[i] >= 3) {
			return true; // Three of a kind
		}
	}

	return false; // No scoring conditions met
}

void Player::scoreDie()
{
}

void Player::displayDice() const
{
	std::cout << "Held dice:" << std::endl;
	for (Die die : heldDice) {
		std::cout << die.displayValue() << " ";
	}
	std::cout << std::endl << "Rolled dice:";
	for (Die die : rollingDice) {
		std::cout << die.displayValue() << " ";
	}
	std::cout << std::endl;
}

void Player::promptForAction()
{
	if (canScoreDie()) {
		std::cout << "Choose an action: (1) Roll Dice (2) Hold Die (3) Score Die and End turn: ";
	} else {
		std::cout << "You cannot score any dice. Your turn is over." << std::endl;
		return;
	}

	int action;

	std::cin >> action;

	switch(action) {
		case 1:
			rollDice();
			break;
		case 2:
			promptForHoldDie();
			break;
		case 3:
			scoreDie();
			std::cout << "Ending turn." << std::endl;
			return; // End the turn
		default:
			std::cout << "Invalid action. Please try again." << std::endl;
			promptForAction();
			return; // Re-prompt for action
	}
}

void Player::promptForHoldDie()
{
	std::cout << "Enter the index of the die to hold (1 to " << rollingDice.size() << ") or enter 7 to roll again: ";
	int index;
	std::cin >> index;

	if (index == 7) {
		rollDice();
		return;
	}

	// Adjust index for 0-based indexing
	index -= 1; // Convert to 0-based index

	if (index < 0 || index >= rollingDice.size()) {
		std::cout << "Invalid index. Please try again." << std::endl;
		promptForHoldDie();
		return; // Re-prompt for holding a die
	}

	holdDie(index);
	displayDice();
	promptForHoldDie();
}
