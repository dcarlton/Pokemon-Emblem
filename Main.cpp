#include <time.h>
#include <windows.h>

#include "SDL.h"

#include "src/Utility/GUI.h"
#include "src/State/GameplayState.h"
#include "src/Utility/Log.h"

void gameLoop();
void loadGame();
void cleanup();

int main()
{
    loadGame();
    gameLoop();
    cleanup();
    return 0;
}

void loadGame()
{
    Utility::initLog();
    GUI::loadEngine();
    GUI::loadAssets();
    GUI::createWindow(240, 240, "Pokemon Emblem");
}

void gameLoop()
{
    SDL_Event event;
    GameplayState state;
    int startTime = 0;
    int frameRate = 0;

    for (;;)
    {
        startTime = SDL_GetTicks();
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
        state.draw();
        GUI::updateWindow();

        frameRate = SDL_GetTicks() - startTime;
        if (frameRate > 16)
            Utility::log("Frame rate below 60 FPS: last frame lasted " + std::to_string(frameRate) + " milliseconds");
        else
            SDL_Delay(16 - frameRate);

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