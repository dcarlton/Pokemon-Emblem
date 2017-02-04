#ifndef POKEMON_H
#define POKEMON_H

#include <memory>
#include <string>

#include "AllianceEnum.h"
#include "Move.h"
#include "../Utility/Point.h"
#include "PokemonEnum.h"
#include "PokemonStats.h"
#include "StatEnum.h"

namespace Gameplay
{

class Pokemon
{
public:
	AllianceEnum alliance = AllianceEnum::Enemy;
    AnimationState animationState = AnimationState::NEUTRALDOWN;
    bool hasMoved = false;
    std::shared_ptr<Move> moves[4];
    std::string name;
    unsigned int num;
    PokemonStats stats;

    Pokemon(std::string pokemonName, unsigned int level, AllianceEnum startingAlliance);
    unsigned int getMaxRange();
    unsigned int getNumMoves();
    void setStatBoost(Stat stat, int statBoost);

private:
    unsigned int validateLevel(unsigned int level);
};

}

#endif
