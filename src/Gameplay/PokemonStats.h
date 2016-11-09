#ifndef POKEMONSTATS_H
#define POKEMONSTATS_H


#include "PokemonEnum.h"


namespace Gameplay
{

class PokemonStats
{
public:
    PokemonStats();
    PokemonStats(PokemonSpecies species, unsigned int level);
    unsigned int getCurrentHP();
    unsigned int getLevel();
    unsigned int getMaxHP();
    unsigned int getMovementRange();
    void takeDamage(int damage);

private:
    unsigned int currentHP;
    unsigned int level;
    unsigned int maxHP;
    unsigned int movement;
};

}


#endif