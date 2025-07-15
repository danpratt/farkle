#include "Die.h"
#include <cstdlib>
#include <iostream>
#include <string>

Die::Die()
{
	// rolls a value at init
	roll();
}

// rolls the dice, stores the value of the roll and also returns the roll
int Die::roll() {
	value = (rand() % 6) + 1;
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
