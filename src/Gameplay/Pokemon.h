#ifndef POKEMON_H
#define POKEMON_H

#include "AllianceEnum.h"
#include "../GUI/GUI.h"
#include "../GUI/ImageEnum.h"
#include "../Utility/Point.h"
#include "PokemonEnum.h"

class GUI::Image;

namespace Gameplay
{

struct PokemonStats
{
    uint32 currentHP = 10;
    uint32 maxHP = 10;
    uint32 movement = 5;
};

class Pokemon
{
public:
	AllianceEnum alliance = AllianceEnum::Enemy;
    AnimationState animationState = AnimationState::NEUTRALDOWN;
    bool hasMoved = false;
    GUI::Image image = GUI::getImage(GUI::ImageEnum::TestPokemon);
    PokemonSpecies species;
    PokemonStats stats;

    Pokemon(PokemonSpecies species, AllianceEnum startingAlliance);
};

}

#endif
