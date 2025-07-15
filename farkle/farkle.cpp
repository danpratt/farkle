// farkle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Player.h"

int main()
{
    // Seed the random number generator once at the start of the program
    srand(static_cast<unsigned int>(time(0)));

    Player p1 = Player("Daniel");
    p1.beginTurn();
}