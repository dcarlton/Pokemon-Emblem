#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include "SDL.h"

#include "../Utility/Color.h"
#include "../Utility/Size.h"

namespace GUI
{

class Image
{
public:
    Size size;
    SDL_Surface* surface;

    Image();
    Image(std::string imageFilename, Utility::Color colorKey, Size sizeArg);
    ~Image();
};

}

#endif