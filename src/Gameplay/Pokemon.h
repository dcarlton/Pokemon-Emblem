#ifndef POKEMON_H
#define POKEMON_H

#include "AllianceEnum.h"
#include "../GUI/GUI.h"
#include "../GUI/ImageEnum.h"
#include "../Utility/Point.h"

class GUI::Image;

namespace Gameplay
{

class Pokemon
{
public:
	AllianceEnum alliance = AllianceEnum::Enemy;
    bool hasMoved = false;
    GUI::Image image = GUI::getImage(GUI::ImageEnum::TestPokemon);
    //Utility::Point position = Utility::Point(0, 0);

    Pokemon(AllianceEnum startingAlliance);
};

}

#endif
