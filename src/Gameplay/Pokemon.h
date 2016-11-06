#ifndef POKEMON_H
#define POKEMON_H

#include "AllianceEnum.h"
#include "../Utility/Point.h"
#include "PokemonEnum.h"

namespace Gameplay
{

struct PokemonStats
{
    uint32 currentHP = 10;
    uint32 level = 1;
    uint32 maxHP = 10;
    uint32 movement = 5;
};

class Pokemon
{
public:
	AllianceEnum alliance = AllianceEnum::Enemy;
    AnimationState animationState = AnimationState::NEUTRALDOWN;
    bool hasMoved = false;
    PokemonSpecies species;
    PokemonStats stats;

    Pokemon(PokemonSpecies species, unsigned int level, AllianceEnum startingAlliance);

private:
    unsigned int validateLevel(unsigned int level);
};

}

#endif
