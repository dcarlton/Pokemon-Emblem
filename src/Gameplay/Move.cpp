#include <fstream>
#include <sstream>

#include "json.hpp"

#include "Move.h"


namespace
{
    // Read info on every move from a file.
    nlohmann::json initMoveInfo()
    {
        std::ifstream movesFile("../moves.json");
        std::stringstream tempStream;
        tempStream << movesFile.rdbuf();
        return nlohmann::json::parse(tempStream.str());
    }

    nlohmann::json movesInfo = initMoveInfo();
}

// Default constructor.
Gameplay::Move::Move()
{
    _accuracy = 50;
    _basePower = 0;
    _name = "???";
}

// Create a move and use the properties from the moves data file.
Gameplay::Move::Move(std::string name)
{
    /* Start at 100% accuracy.
     -5% for a simple status chance (e.g. 10% chance to paralyze)
    -15% for a better status chance (e.g. 30% chance to burn)
    -25% for a great bonus effect (Sleep Powder)

    -10% for attacks with 40-55 base power
    -15% for attacks with 60-75 base power
    -20% for attacks with 80-100 base power
    -30% for attacks with 120-150 base power

    -10% for attacks with >1 range
    */

    // TODO: Catch errors.
    _accuracy = movesInfo[name]["accuracy"];
    _basePower = movesInfo[name]["basePower"] / 10;
    _name = movesInfo[name]["name"];
}

/// Using private variables with get methods because they shouldn't be changed
/// after the constructor sets them.

// Return the accuracy of this move as a number from 0-100,
// meaning 0%-100%.
unsigned int Gameplay::Move::getAccuracy()
{
    return _accuracy;
}

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