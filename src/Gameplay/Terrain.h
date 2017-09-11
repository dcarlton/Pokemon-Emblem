#ifndef TERRAIN_H
#define TERRAIN_H


#include "../Utility/Point.h"

namespace Gameplay
{

class Terrain
{
public:
    Terrain();
    Terrain(Utility::Point imageIndex, int avoid, int defense);
    int getAvoid();
    int getDefense();
    Utility::Point getImageIndex();

private:
    int _avoid;
    int _defense;
    Utility::Point _imageIndex;
};

}

#endif