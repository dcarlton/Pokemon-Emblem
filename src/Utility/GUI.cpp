// TODO: Probably shouldn't assert on error

#include <assert.h>
#include <string>

#include "SDL.h"

#include "GUI.h"


namespace
{
    static SDL_Window *window = nullptr;
    static SDL_Surface *windowSurface = nullptr;
}


void GUI::cleanup()
{
    deleteWindow();
    SDL_Quit();
}

void GUI::createWindow(int width, int height, std::string title)
{
    deleteWindow();
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    assert(window);
    windowSurface = SDL_GetWindowSurface(window);
}

void GUI::deleteWindow()
{
    SDL_DestroyWindow(window);
    SDL_FreeSurface(windowSurface);
}

void GUI::drawImage(SDL_Surface* imageSurface, int x, int y, int width, int height)
{
    SDL_Rect targetRect;
    targetRect.x = x;
    targetRect.y = y;
    targetRect.h = height;
    targetRect.w = width;
    SDL_BlitSurface(imageSurface, NULL, windowSurface, &targetRect);
}

SDL_Surface* GUI::getImage(const std::string imageFilename)
{
    return SDL_LoadBMP(imageFilename.c_str());
}

void GUI::loadAssets()
{
}

void GUI::loadEngine()
{
    int error = SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    assert(!error);
}

void GUI::updateWindow()
{
    SDL_UpdateWindowSurface(window);
}