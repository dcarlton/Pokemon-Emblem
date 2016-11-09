#ifndef POKEMON_H
#define POKEMON_H

#include "AllianceEnum.h"
#include "../Utility/Point.h"
#include "PokemonEnum.h"
#include "PokemonStats.h"

namespace Gameplay
{

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
