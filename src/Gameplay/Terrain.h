#ifndef TERRAIN_H
#define TERRAIN_H


#include "../Utility/Point.h"

namespace Gameplay
{

class Terrain
{
public:
    int xImageIndex;
    int yImageIndex;

    Terrain();
    Terrain(Utility::Point imageOffset);
};

}

#endif