#include "Image.h"
#include "../Utility/Log.h"

GUI::Image::Image()
{
    size = Size(0, 0);
    surface = nullptr;
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

GUI::Image::~Image()
{
}