#include <time.h>
#include <windows.h>

#include "SDL.h"

#include "src/GUI/GUI.h"
#include "src/State/GameplayState.h"
#include "src/Utility/Log.h"
#include "src/Utility/Size.h"

void gameLoop();
void loadGame();
void cleanup();

int main()
{
    loadGame();
    try
    {
        gameLoop();
    }
    catch(...)
    {
    }
    cleanup();
    return 0;
}

void loadGame()
{
    Utility::initLog();
    GUI::loadEngine();
    GUI::loadAssets();
    GUI::createWindow(Size(240, 240), "Pokemon Emblem");
}

void gameLoop()
{
    SDL_Event event;
    GameplayState state;
    //int startTime = 0;
    //int frameRate = 0;

    for (;;)
    {
        //GUI::showMessage("Begin game loop");
        //startTime = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_DOWN:
                            state.moveDownPressed();
                            break;

                        case SDLK_LEFT:
                            state.moveLeftPressed();
                            break;

                        case SDLK_RIGHT:
                            state.moveRightPressed();
                            break;

                        case SDLK_UP:
                            state.moveUpPressed();
                            break;

                        case SDLK_ESCAPE:
                            return;
                    }
                    break;

                case SDL_QUIT:
                    return;
            }
        }

        state.update();
        //GUI::showMessage("Start drawing");
        state.draw();
        //GUI::showMessage("Finished drawing");
        GUI::updateWindow();
        //GUI::showMessage("Finish updating window");

        /*frameRate = SDL_GetTicks() - startTime;
        if (frameRate > 16)
            Utility::log("Frame rate below 60 FPS: last frame lasted " + std::to_string(frameRate) + " milliseconds");
        else
            SDL_Delay(16 - frameRate);*/
        //GUI::showMessage("End game loop");
    }
}

void cleanup()
{
    Utility::quitLog();
    GUI::cleanup();
}

// VS Windows applications need WinMain as an entry point
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    return main();
}