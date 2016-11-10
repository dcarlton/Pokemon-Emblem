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
    int getAttack();
    int getCurrentHP();
    int getDefense();
    unsigned int getLevel();
    unsigned int getMaxHP();
    unsigned int getMovementRange();
    void takeDamage(int damage);

private:
    int attack;
    int currentHP;
    int defense;
    unsigned int level;
    unsigned int maxHP;
    unsigned int movement;
};

}


#endif