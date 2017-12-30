#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

#include "json.hpp"

#include "../Utility/Log.h"
#include "Move.h"
#include "Pokemon.h"


namespace
{
    // Read info on every move from a file.
    nlohmann::json initMoveInfo()
    {
        std::ifstream movesFile("moves.json");
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
    doesDamage = true;
    _name = "???";
    _range = 0;
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
    _alwaysHits = movesInfo[name]["alwaysHits"];
    _basePower = (unsigned int)movesInfo[name]["basePower"];
    _damageType = movesInfo[name]["damageType"];
    _name = movesInfo[name]["name"];
    
    // Determine range.
    std::string targetType = movesInfo[name]["target"];
    if (targetType == "normal")
    {
        _range = 1;
        _target = TARGET::ENEMY;
    }
    else if (targetType == "allAdjacentFoes")
    {
        // TODO: This should hit everyone within a radius, instead of one targeted foe.
        _range = 2;
        _target = TARGET::ENEMY;
    }
    else if (targetType == "adjacentAlly")
    {
        _range = 1;
        _target = TARGET::ALLY;
    }
    else
        _range = 0;


    // Determine if the move lowers the opponent's stats.
    if (movesInfo[name].count("targetBoosts") == 1)
    {
        nlohmann::json targetBoosts = movesInfo[name]["targetBoosts"];

        // This is 6 if's, and not a series of else-ifs, on purpose.
        if (targetBoosts.count("atk") == 1)
        {
            addTargetBoostSideEffect(Gameplay::Stat::ATTACK, targetBoosts["atk"]);
        }
        if (targetBoosts.count("def") == 1)
        {
            addTargetBoostSideEffect(Gameplay::Stat::DEFENSE, targetBoosts["def"]);
        }
        if (targetBoosts.count("spa") == 1)
        {
            addTargetBoostSideEffect(Gameplay::Stat::SPECIAL_ATTACK, targetBoosts["spa"]);
        }
        if (targetBoosts.count("spd") == 1)
        {
            addTargetBoostSideEffect(Gameplay::Stat::SPECIAL_DEFENSE, targetBoosts["spd"]);
        }
        if (targetBoosts.count("spe") == 1)
        {
            addTargetBoostSideEffect(Gameplay::Stat::SPEED, targetBoosts["spe"]);
        }
    }
}

// Add a side effect to this move, which gives a stat bonus for the given stat.
void Gameplay::Move::addTargetBoostSideEffect(Gameplay::Stat stat, int statBoost)
{
    _sideEffects.push_back([stat, statBoost](std::shared_ptr<Gameplay::Pokemon> attackingPokemon, std::shared_ptr<Gameplay::Pokemon> targetPokemon)
    {
        targetPokemon->stats.setStatBoost(stat, statBoost);
    });
}

bool Gameplay::Move::alwaysHits()
{
    return _alwaysHits;
}

int Gameplay::Move::calculateDamage(int attack, int defense)
{
    if (_damageType == "noDamage")
    {
        // This move does no damage.
        return 0;
    }
    else if (_damageType == "basePower")
    {
        // This move does damage based on its power, the user's attack,
        // and the target's defense.
        return std::max(0, (attack + (int)_basePower) - defense);
    }
    else if (_damageType == "rawHealing")
    {
        // This move does a percentage of damage based on the target's health.
        return -(int)_basePower;
    }
    else
    {
        Utility::log("Unknown damage type used: " + _damageType);
        return 0;
    }
}

bool Gameplay::Move::canTarget(std::shared_ptr<Gameplay::Pokemon> attacker, std::shared_ptr<Gameplay::Pokemon> defender)
{
    if (attacker->alliance == defender->alliance && _target & TARGET::ALLY && attacker != defender)
    {
        return true;
    }
    else if (attacker->alliance != defender->alliance && _target & TARGET::ENEMY)
    {
        return true;
    }
    else if (_target & TARGET::SELF && attacker == defender)
    {
        return true;
    }

    return false;
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

// Gets the move's range.
unsigned int Gameplay::Move::getRange()
{
    return _range;
}

unsigned int Gameplay::Move::getTarget()
{
    return _target;
}

// Run all side effects (Non-damaging effects) of this move on the
// two Pokemon involved.
void Gameplay::Move::runSideEffects(std::shared_ptr<Gameplay::Pokemon> attackingPokemon, std::shared_ptr<Gameplay::Pokemon> targetPokemon)
{
    for (unsigned int i = 0; i < _sideEffects.size(); i++)
    {
        _sideEffects[i](attackingPokemon, targetPokemon);
    }
}