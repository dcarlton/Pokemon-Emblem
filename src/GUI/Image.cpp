#include "Image.h"
#include "../Utility/Log.h"

GUI::Image::Image()
{
    Utility::log("Image object created without an image file");
}

GUI::Image::Image(std::string imageFilename, Utility::Color rgb, Size sizeArg)
{
    surface = SDL_LoadBMP(imageFilename.c_str());
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

// TODO: Clean up surfaces. Either taken care of once every tile isn't given
// the default tile, or use a RAII hashmap system to delete surface when
// nothing is using it
GUI::Image::~Image()
{
}