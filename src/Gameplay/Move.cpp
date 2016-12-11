#include "Move.h"


// Default constructor.
Gameplay::Move::Move()
{
    _basePower = 0;
    _name = "???";
}

// Create a move and use the properties from the moves data file.
// TODO: Load attack info from a data file based on their name.
Gameplay::Move::Move(std::string name)
{
    _name = name;

    if (name == "A")
    {
        _basePower = 5;
    }
    else if (name == "B")
    {
        _basePower = 10;
    }
    else
    {
        _basePower = 0;
    }
}

/// Using private variables with get methods because they shouldn't be changed
/// after the constructor sets them.

// Gets the move's base power.
unsigned int Gameplay::Move::getBasePower()
{
    return _basePower;
}

// Gets the move's name.
std::string Gameplay::Move::getName()
{
    return _name;
}