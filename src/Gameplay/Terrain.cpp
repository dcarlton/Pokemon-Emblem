#include "Terrain.h"

Gameplay::Terrain::Terrain()
{
    _avoid = 0;
    _defense = 0;
    _imageIndex = Utility::Point(0, 0);
}

Gameplay::Terrain::Terrain(Utility::Point imageIndex, int avoid, int defense)
{
    _avoid = avoid;
    _defense = defense;
    _imageIndex = imageIndex;
}

int Gameplay::Terrain::getAvoid()
{
    return _avoid;
}

int Gameplay::Terrain::getDefense()
{
    return _defense;
}

Utility::Point Gameplay::Terrain::getImageIndex()
{
    return _imageIndex;
}