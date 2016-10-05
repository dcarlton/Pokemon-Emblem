#ifndef POKEMON_H
#define POKEMON_H

#include "AllianceEnum.h"
#include "../GUI/GUI.h"
#include "../GUI/ImageEnum.h"
#include "../Utility/Point.h"

class GUI::Image;

namespace Gameplay
{

struct PokemonStats
{
    uint32 movement = 5;
};

class Pokemon
{
public:
	AllianceEnum alliance = AllianceEnum::Enemy;
    bool hasMoved = false;
    GUI::Image image = GUI::getImage(GUI::ImageEnum::TestPokemon);
    PokemonStats stats;

    Pokemon(AllianceEnum startingAlliance);
};

}

#endif
