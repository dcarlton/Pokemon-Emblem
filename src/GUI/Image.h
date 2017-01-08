#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include "SDL.h"

#include "../Utility/Color.h"
#include "../Utility/Point.h"


namespace GUI
{

class Image
{
public:
    Utility::Point size = Utility::Point(0, 0);
    SDL_Surface* surface = new SDL_Surface();

    Image();
    Image(std::string imageFilename, Utility::Color colorKey, Utility::Point sizeArg);
    Image(const Image& that);
    ~Image();
    Image& operator=(const Image& that);
};

}

#endif