#ifndef TILE_H
#define TILE_H

#include <memory>

#include "../Utility/Point.h"
#include "Pokemon.h"
#include "Terrain.h"


namespace Gameplay
{

class Tile
{
public:
    std::shared_ptr<Pokemon> pokemon = nullptr;
    Terrain terrain;
};

}

#endif