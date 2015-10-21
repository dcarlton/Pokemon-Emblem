#include "../GUI/GUI.h"
#include "../Utility/Point.h"
#include "Tile.h"


void Gameplay::Tile::draw(Utility::Point const &pos)
{
    GUI::drawImage(terrain.image, pos);
    if (pokemon)
        GUI::drawImage(pokemon->image, pos);
}