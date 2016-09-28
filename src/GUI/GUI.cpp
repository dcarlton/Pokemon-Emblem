#include "SDL_TTF.h"

#include "GUI.h"
#include "ImageFactory.h"
#include "../Utility/Log.h"
#include "../Utility/Size.h"


namespace
{
    static SDL_Window *window = nullptr;
    static SDL_Surface *windowSurface = nullptr;
}


void GUI::cleanup()
{
    deleteWindow();
    TTF_Quit();
    SDL_Quit();
}

void GUI::createWindow(Utility::Size size, std::string title)
{
    deleteWindow();
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.width, size.height, 0);
    if (!window)
        Utility::log("Failed to create a window with size " +
                     size.to_string() +
                     " and title " +
                     title);
    windowSurface = SDL_GetWindowSurface(window);
}

void GUI::deleteWindow()
{
    if (!window || !windowSurface)
        Utility::log("Attempting to delete a window when a window has not been created");
    SDL_DestroyWindow(window);
    SDL_FreeSurface(windowSurface);
}

void GUI::drawImage(GUI::Image image, Utility::Point position)
{
    if (!image.surface || !windowSurface)
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
    if (error != 0)
        Utility::log("Unabe to initialize SDL: " + std::string(SDL_GetError()));

    if (TTF_Init() < 0)
        Utility::log("Unable to initialize SDL_TTF: ");
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