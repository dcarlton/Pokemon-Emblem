#include "SDL.h"

#include "../../src/Data/Image.h"
#include "../../src/Utility/GUI.h"
#include "Terrain.h"

Terrain::Terrain()
{
    image = GUI::getImage(Image::testTile);
}