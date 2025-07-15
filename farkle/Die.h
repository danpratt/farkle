

#pragma once
#include <string>

class Die
{
private:
	// holds the roll value
	int value;

public:
	// constructor
	Die();

	// simulates a roll and updates value
	int roll();

	// returns the current value of the die
	int getValue() const;

	std::string displayValue() const;
};

