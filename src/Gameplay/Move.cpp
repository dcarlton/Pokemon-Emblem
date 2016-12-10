#include "Move.h"


// Default constructor.
Gameplay::Move::Move()
{
    basePower = 10;
    name = "???";
}

// Create a move and use the properties from the moves data file.
// TODO: Load attack info from a data file based on their name.
Gameplay::Move::Move(std::string name)
{
    basePower = 9001;
    this->name = name;
}

/// Using private variables with get methods because they shouldn't be changed
/// after the constructor sets them.

// Gets the move's base power.
unsigned int Gameplay::Move::getBasePower()
{
    return basePower;
}

// Gets the move's name.
std::string Gameplay::Move::getName()
{
    return name;
}