#include "../Filesystem/Pokedex.h"
#include "PokemonStats.h"


// Default constructor.
Gameplay::PokemonStats::PokemonStats()
{
    attack = 0;
    currentHP = 0;
    defense = 0;
    level = 1;
    maxHP = 0;
    movement = 0;
}

// Initializes the Pokemon's stats, using the Pokemon species
// and level to calculate stats.
Gameplay::PokemonStats::PokemonStats(std::string name, unsigned int level)
{
    Filesystem::Pokedex::BaseStats baseStats = Filesystem::Pokedex::getBaseStats(name);
    maxHP = (baseStats.hp / 5) + 12;
    currentHP = maxHP;
    attack = baseStats.attack / 20;
    defense = baseStats.defense / 20;
    this->level = level;
    setMovementRange(baseStats.speed);
}

// Side note: I'm using a lot of "getVariable" methods because
// I don't want to set them directly. Setting variables like HP
// directly can easily cause bugs, so I'm making all variables
// private and using get methods.

int Gameplay::PokemonStats::getAttack()
{
    return attack;
}

int Gameplay::PokemonStats::getCurrentHP()
{
    return currentHP;
}

int Gameplay::PokemonStats::getDefense()
{
    return defense;
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

// Sets the movement range based on the Pokemon's base speed.
void Gameplay::PokemonStats::setMovementRange(unsigned int baseSpeed)
{
    if (baseSpeed >= 120)
        movement = 8;
    else if (baseSpeed >= 100)
        movement = 7;
    else if (baseSpeed >= 70)
        movement = 6;
    else if (baseSpeed >= 40)
        movement = 5;
    else
        movement = 4;
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