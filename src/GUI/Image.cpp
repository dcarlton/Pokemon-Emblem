#include <assert.h>

#include "Image.h"
#include "../Utility/Log.h"

GUI::Image::Image()
{
    Utility::log("Image object created without an image file");
}

GUI::Image::Image(std::string imageFilename, Utility::Color rgb, Utility::Size sizeArg)
{
    SDL_FreeSurface(surface);
    *surface = *SDL_LoadBMP(imageFilename.c_str());
    if (!surface)
    {
        Utility::log(SDL_GetError());
    }
    else
    {
        int colorKey = SDL_MapRGB(surface->format, rgb.red, rgb.green, rgb.blue);
        SDL_SetColorKey(surface, SDL_TRUE, colorKey);
    }
    size = sizeArg;
}

// Copy constructor. We need to make sure the surface is a complete
// and separate copy. If multiple Images point to the same surface, it'll
// be freed twice, causing a crash.
//
// This is called when an image is pushed into a vector, and maybe similar
// situations.
GUI::Image::Image(const Image& that)
{
    size = that.size;
    if (surface != nullptr)
        *surface = *that.surface;
}

// TODO: Clean up surfaces. Either taken care of once every tile isn't given
// the default tile, or use a RAII hashmap system to delete surface when
// nothing is using it
GUI::Image::~Image()
{
    //SDL_FreeSurface(surface);
    delete surface;
}

// Rewriting the assignment operator so that a distinct copy
// of the surface is made. See the copy constructor for more details.
GUI::Image& GUI::Image::operator=(const Image& that)
{
    size = that.size;
    *surface = *that.surface;
    return *this;
}