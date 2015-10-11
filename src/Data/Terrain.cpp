#include "../GUI/GUI.h"
#include "Terrain.h"

Terrain::Terrain()
{
    image = GUI::getImage(GUI::ImageEnum::TestTile);
}