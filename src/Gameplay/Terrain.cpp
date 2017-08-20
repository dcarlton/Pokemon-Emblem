#include "Terrain.h"

Gameplay::Terrain::Terrain()
{
    xImageIndex = 0;
    yImageIndex = 0;
}

Gameplay::Terrain::Terrain(Utility::Point imageOffset)
{
    xImageIndex = imageOffset.x;
    yImageIndex = imageOffset.y;
}