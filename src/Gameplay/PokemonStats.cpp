#include "PokemonStats.h"


// Default constructor.
Gameplay::PokemonStats::PokemonStats()
{
    currentHP = 0;
    level = 1;
    maxHP = 0;
    movement = 0;
}

// Initializes the Pokemon's stats, using the Pokemon species
// and level to calculate stats.
Gameplay::PokemonStats::PokemonStats(Gameplay::PokemonSpecies species, unsigned int level)
{
    currentHP = level * 3;
    this->level = level;
    maxHP = level * 3;
    movement = 5;
    species;
}

// Side note: I'm using a lot of "getVariable" methods because
// I don't want to set them directly. Setting variables like HP
// directly can easily cause bugs, so I'm making all variables
// private and using get methods.

unsigned int Gameplay::PokemonStats::getCurrentHP()
{
    return currentHP;
}

unsigned int Gameplay::PokemonStats::getLevel()
{
    return level;
}

unsigned int Gameplay::PokemonStats::getMaxHP()
{
    return maxHP;
}

unsigned int Gameplay::PokemonStats::getMovementRange()
{
    return movement;
}

// Remove the amount of damage taken from this Pokemon's current HP.
// Don't take any damage if the value is negative.
void Gameplay::PokemonStats::takeDamage(int damage)
{
    if (damage < 0)
        damage = 0;
    else if (damage > (int)currentHP)
        damage = currentHP;

    currentHP -= damage;
}