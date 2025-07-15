#include "Player.h"
#include <iostream>

Player::Player(std::string name)
{
	this->name = name;
}

std::string Player::getName() const
{
	return name;
}

void Player::beginTurn()
{
	// overwrite rollingDice vector with new dice
	rollingDice = { Die(), Die(), Die(), Die(), Die(), Die() };
	displayDice();
}

void Player::rollDice()
{
}

void Player::holdDie(int atIndex)
{
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
}
