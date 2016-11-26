#ifndef POKEMON_H
#define POKEMON_H

#include <string>

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
    std::string name;
    unsigned int num;
    PokemonStats stats;

    Pokemon(std::string pokemonName, unsigned int level, AllianceEnum startingAlliance);

private:
    unsigned int validateLevel(unsigned int level);
};

}

#endif
