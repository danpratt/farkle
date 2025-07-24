#include "Die.h"
#include <cstdlib>
#include <iostream>
#include <string>

std::mt19937 Die::gen(std::random_device{}());

Die::Die()
{
	// rolls a value at init
	roll();
}

// rolls the dice, stores the value of the roll and also returns the roll
int Die::roll() {
	std::uniform_int_distribution<> distrib(1, 6);
	value = distrib(gen);
	return value;
}

// returns the value of the dice
int Die::getValue() const {
	return value;
}

std::string Die::displayValue() const {  
	std::string visual;
	visual.append("[");
	visual.append(std::to_string(value));
	visual.append("]");
	return visual;
}
