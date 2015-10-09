#ifndef POKEMON_H
#define POKEMON_H

#include "../../src/Data/Image.h"
#include "../../src/Utility/GUI.h"
#include "../../src/Utility/Point.h"

class Pokemon
{
public:
    SDL_Surface* image = GUI::getImage(Image::testPokemon);
    Point position = Point(0, 0);

    Pokemon();
};

#endif