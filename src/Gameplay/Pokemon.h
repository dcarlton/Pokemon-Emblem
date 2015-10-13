#ifndef POKEMON_H
#define POKEMON_H

#include "../GUI/GUI.h"
#include "../GUI/ImageEnum.h"
#include "../Utility/Point.h"

class GUI::Image;

namespace Gameplay
{

class Pokemon
{
public:
    GUI::Image image = GUI::getImage(GUI::ImageEnum::TestPokemon);
    Utility::Point position = Utility::Point(0, 0);

    Pokemon();
};

}

#endif