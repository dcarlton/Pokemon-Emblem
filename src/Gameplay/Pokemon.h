#ifndef POKEMON_H
#define POKEMON_H

#include <array>
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
    std::array<std::shared_ptr<Move>, 4> moves;
    std::string name;
    unsigned int num;
    PokemonStats stats;

    Pokemon(std::string pokemonName, unsigned int level, AllianceEnum startingAlliance);
    unsigned int getMaxRange();
    unsigned int getNumMoves();
    void onStartTurn();

private:
    unsigned int validateLevel(unsigned int level);
};

}

#endif
