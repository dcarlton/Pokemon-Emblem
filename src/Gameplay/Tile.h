#ifndef TILE_H
#define TILE_H

#include <memory>

#include "Pokemon.h"
#include "Terrain.h"


class Utility::Point;

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