#include <algorithm>
#include <math.h>
#include <stdlib.h>

#include "../Filesystem/Pokedex.h"
#include "PokemonStats.h"


// Default constructor.
Gameplay::PokemonStats::PokemonStats()
{
    attack = 0;
    currentHP = 0;
    defense = 0;
    level = 1;
    luck = 0;
    maxHP = 0;
    movement = 0;
    skill = 0;
    speed = 0;
}

// Initializes the Pokemon's stats, using the Pokemon species
// and level to calculate stats.
Gameplay::PokemonStats::PokemonStats(std::string name, unsigned int level)
{
    setLevelOneStats(name);
    levelUpNormalized(name, level - 1);
    this->level = level;
}

// Side note: I'm using a lot of "getVariable" methods because
// I don't want to set them directly. Setting variables like HP
// directly can easily cause bugs, so I'm making all variables
// private and using get methods.

unsigned int Gameplay::PokemonStats::getAccuracy()
{
    return skill * 2;
}

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

unsigned int Gameplay::PokemonStats::getEvasion()
{
    return (speed * 2) + luck;
}

unsigned int Gameplay::PokemonStats::getLevel()
{
    return level;
}

unsigned int Gameplay::PokemonStats::getLuck()
{
    return luck;
}

unsigned int Gameplay::PokemonStats::getMaxHP()
{
    return maxHP;
}

unsigned int Gameplay::PokemonStats::getMovementRange()
{
    return movement;
}

unsigned int Gameplay::PokemonStats::getSkill()
{
    return skill;
}

unsigned int Gameplay::PokemonStats::getSpeed()
{
    return speed;
}

// Level up the stats one or more times, using the growth rate of
// the given Pokemon's stats, averaged out and slightly randomized.
void Gameplay::PokemonStats::levelUpNormalized(std::string name, unsigned int numLevelUps)
{
    Filesystem::Pokedex::BaseStats evolvedBaseStats = Filesystem::Pokedex::getEvolvedBaseStats(name);
    maxHP += roundRandomly(numLevelUps * (evolvedBaseStats.hp / 100.0));
    currentHP = maxHP;
    attack += roundRandomly(numLevelUps * (evolvedBaseStats.attack / 200.0));
    skill += roundRandomly(numLevelUps * (std::min(evolvedBaseStats.attack, evolvedBaseStats.spAttack) / 150.0));
    speed += roundRandomly(numLevelUps * (evolvedBaseStats.speed / 200.0));
    luck += roundRandomly(numLevelUps * ((80 - (10 * (log10(evolvedBaseStats.catchRate) / log10(3)))) / 100));
    defense += roundRandomly(numLevelUps * (evolvedBaseStats.defense / 400.0));
}

// Round a number up or down at random. The odds that it will round
// up is equal to the value after the decimal, as a percentage.
unsigned int Gameplay::PokemonStats::roundRandomly(double num)
{
    // e.g. 1.5 * 100 = 150, 150 % 100 = 50
    // Thus, 1.5 has a 50% chance of being round up.
    int numAfterDecimal = (int(num * 100)) % 100;

    // A random number mod 100 is between 0 and 99.
    // If the random number is smaller than the number after
    // the decimal, then we round up. Thus, 1.01 has a 1% chance
    // of rounding up.
    if (rand() % 100 < numAfterDecimal)
        return (unsigned int)ceil(num);
    else
        return (unsigned int)floor(num);
}

// Set the stats to the starting stats of the given Pokemon.
void Gameplay::PokemonStats::setLevelOneStats(std::string name)
{
    Filesystem::Pokedex::BaseStats baseStats = Filesystem::Pokedex::getBaseStats(name);
    maxHP = (baseStats.hp / 5) + 12;
    currentHP = maxHP;
    attack = baseStats.attack / 20;
    skill = std::min(baseStats.attack, baseStats.spAttack) / 15;
    speed = baseStats.speed / 20;

    // base 2 log of x = base y log(x) / base y log(2). y doesn't matter.
    int logBase3CatchRate = (int)(log10(baseStats.catchRate) / log10(3));

    // Logarithms! Catch rates range from 255 to 3, this smooths the differences out
    // to a linear scale.
    luck = 2 * (6 - logBase3CatchRate);

    defense = baseStats.defense / 20;

    setMovementRange(baseStats.speed);
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