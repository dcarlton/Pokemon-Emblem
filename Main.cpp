#include <exception>
#include <time.h>
#include <windows.h>

#include "SDL.h"

#include "src/State/GameplayState.h"
#include "src/GUI/GUI.h"
#include "src/Utility/Log.h"
#include "src/Utility/Size.h"
#include "src/State/State.h"


class QuitException: public std::exception{};

void loadGame();
void gameLoop();
void processInput(State::State &state);
void cleanup();

int main()
{
    try
    {
        loadGame();
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
    GUI::createWindow(Utility::Size(240, 240), "Pokemon Emblem");
}

void gameLoop()
{
    State::GameplayState state;
    int frameRate = 0;
    int startTime = 0;

    try
    {
        for (;;)
        {
            startTime = SDL_GetTicks();

            processInput(state);
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
    catch (QuitException)
    {
    }
}

void processInput(State::State &state)
{
    SDL_Event event;
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
                        throw QuitException();
                }
                break;

            case SDL_QUIT:
                throw QuitException();
        }
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