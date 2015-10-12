#ifndef TERRAIN_H
#define TERRAIN_H

#include "../GUI/GUI.h"
#include "../GUI/ImageEnum.h"

class GUI::Image;

namespace Gameplay
{

class Terrain
{
public:
    Terrain();
    GUI::Image image = GUI::getImage(GUI::ImageEnum::TestTile);
};

}

#endif