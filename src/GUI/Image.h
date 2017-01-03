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
    Utility::Size size = Utility::Size(0, 0);
    SDL_Surface* surface = new SDL_Surface();

    Image();
    Image(std::string imageFilename, Utility::Color colorKey, Utility::Size sizeArg);
    Image(const Image& that);
    ~Image();
    Image& operator=(const Image& that);
};

}

#endif