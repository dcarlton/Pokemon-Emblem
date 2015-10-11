// TODO: Probably shouldn't assert on error

#include <assert.h>

#include "GUI.h"
#include "ImageFactory.h"
#include "../Utility/Log.h"


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

void GUI::drawImage(GUI::Image image, Point position)
{
    if (image.surface == nullptr || windowSurface == nullptr)
        return;

    SDL_Rect targetRect;
    targetRect.x = position.x;
    targetRect.y = position.y;
    targetRect.h = image.size.height;
    targetRect.w = image.size.width;

    SDL_BlitSurface(image.surface, NULL, windowSurface, &targetRect);
}

GUI::Image GUI::getImage(ImageEnum imageEnum)
{
    return makeImage(imageEnum);
}

void GUI::loadAssets()
{
}

void GUI::loadEngine()
{
    int error = SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    assert(!error);
}

void GUI::showMessage(std::string message)
{
    SDL_ShowSimpleMessageBox(0,
                             "",
                             message.c_str(),
                             window);

}

void GUI::updateWindow()
{
    SDL_UpdateWindowSurface(window);
}