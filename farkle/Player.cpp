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
	std::cout << "It's " << name << "'s turn!" << std::endl;
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
	if (!canScoreDie()) {
		std::cout << "No scoring dice rolled. Ending turn." << std::endl;
		return; // End the turn if no scoring dice
	}
	else {
		promptForAction();
	}
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

bool Player::heldDieAreValid() {
	int counts[6] = { 0 };  // Array to count occurences of each die value (1-6)
	for (const Die& die : heldDice) {
		if (die.getValue() >= 1 && die.getValue() <= 6) {
			counts[die.getValue() - 1]++;
		}
	}

	for (int i = 0; i < 6; i++) {
		// no matter how many ones or fives we have it is valid, so no need to check those
		if (i != 0 && i != 4) {
			// make sure there is a valid count
            if (counts[i] != 0 && counts[i] != 3 && counts[i] != 6) {
				std::cout << "Invalid held dice." << std::endl;
				return false;
			}
		}
	}

	return true;
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

static bool comp(Die a, Die b) {
	return a.getValue() < b.getValue();
}

void Player::cleanupScorableDice() {
	// count occurrences of each die value in heldDice
	int* counts = createHeldDieCounter();
	// check the counts
	for (int i = 0; i < 6; i++) {
		int numToMove = 0;
		int dieValueToCheck = i + 1;
		// 1's and 5's are always valid so we can skip those
		if (i == 0 || i == 4) { continue; }
		// no work needs to be done if there are 0 die for this number
		if (counts[i] == 0) { continue; }
		if (counts[i] > 3 && counts[i] < 6) {
			// we should leave 3 die in this case
			numToMove = counts[i] - 3;
		}
		// in this case we should remove all the dice
		else if (counts[i] < 3) {
			numToMove = counts[i];
		}

		// do the actual moving of dice
        for (auto it = heldDice.rbegin(); it != heldDice.rend(); /* No automatic increment */) {
			// we found the value, now move it from held dice to rolling dice
			if (it->getValue() == dieValueToCheck) {
				rollingDice.push_back(*it);
				it = std::vector<Die>::reverse_iterator(heldDice.erase(std::next(it).base())); // Erase and update iterator
				numToMove--;
				if (numToMove == 0) break;
			} else {
				++it; // Increment iterator if no match
			}
		}
	}
}

int* Player::createHeldDieCounter() const {  
	// count occurrences of each die value in heldDice  
	static int counts[6] = { 0 }; // Array to count occurrences of each die value (1-6)  
	for (const Die& die : heldDice) {  // Removed 'this->' as it is unnecessary in non-static member functions
		if (die.getValue() >= 1 && die.getValue() <= 6) {  
			counts[die.getValue() - 1]++;  
		}
	}  

	return counts;  
}

void Player::scoreDie()
{
	// make sure the player has dice to score
	if (heldDice.empty()) {
		std::cout << "No dice held to score." << std::endl;
		return;
	}

	// count occurrences of each die value in heldDice
	int counts[6] = { 0 }; // Array to count occurrences of each die value (1-6)
	for (const Die& die : heldDice) {
		if (die.getValue() >= 1 && die.getValue() <= 6) {
			counts[die.getValue() - 1]++;
		}
	}

	// Calculate score based on heldDice
	int turnScore = 0;
	for (int i = 0; i < 6; ++i) {
		while (counts[i] > 0) {
			// scoring for 1's
			if (i == 0) {
				// check for 3 of a kind first
				if (counts[0] >= 3) {
					turnScore += 1000;
					counts[0] -= 3;
				}
				else if (counts[0] > 0 && counts[0] < 3) {
					turnScore += 100;
					counts[0] -= 1;
				}
			}
			// scoring for 5's
			else if (i == 4) {
				if (counts[4] >= 3) {
					turnScore += 500;
					counts[4] -= 3;
				}
				else if (counts[4] > 0 && counts[0] < 3) {
					turnScore += 50;
					counts[4] -= 1;
				}
			}
			// scoring for everything else
			else {
				if (counts[i] >= 3) {
					turnScore += (counts[i] + 1) * 100;
					counts[i] -= 3;
				}
			}
		}
	}

	score += turnScore;
	std::cout << "Scored " << turnScore << " points this turn. Total score: " << score << std::endl;
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
	std::cout << "Choose an action: (1) Roll Dice (2) Hold Die (3) Score Die and End turn: ";

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
			if (heldDieAreValid()) {
				scoreDie();
				std::cout << "Ending turn." << std::endl;
				return; // End the turn
			}
			else {
				cleanupScorableDice();
				displayDice();
				promptForAction();
			}
		default:
			std::cout << "Invalid action. Please try again." << std::endl;
			promptForAction();
			return; // Re-prompt for action
	}
}

void Player::promptForHoldDie()
{
	std::cout << "Enter the index of the die to hold (1 to " << rollingDice.size() << ") or enter 7 to return to the menu: ";
	int index;
	std::cin >> index;

	if (index == 7) {
		promptForAction();
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
	promptForHoldDie();
}
