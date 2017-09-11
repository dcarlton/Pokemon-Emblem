// Uncomment this line to ignore all assertions.
//#define NDEBUG

#ifdef _WIN32
    #include <windows.h>
#endif


#include <assert.h>
#include <exception>
#include <memory>
#include <stdlib.h>
#include <time.h>

#include "SDL.h"

#include "src/Audio/DJ.h"

#include "src/GUI/GUI.h"
#include "src/Utility/Log.h"
#include "src/Filesystem/Maps.h"
#include "src/Filesystem/Options.h"
#include "src/State/PlayerTurnState.h"
#include "src/Utility/Point.h"
#include "src/State/State.h"
#include "src/State/StateStack.h"
#include "src/Gameplay/World.h"


class QuitException: public std::exception{};

void loadGame();
void gameLoop();
void processInput(std::shared_ptr<State::State> state);
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
        Utility::log("Crashed with unknown exception.");
        assert(false);
    }

    cleanup();
    return 0;
}

void loadGame()
{
    srand((unsigned int)time(NULL));
    Utility::initLog();
    Filesystem::LoadIniFile();
    GUI::loadEngine();
    GUI::loadAssets();
    Audio::initAudio();
    GUI::createWindow(Utility::Point(320, 320), "Pokemon Emblem");
}

void gameLoop()
{
    std::shared_ptr<Gameplay::World> world = Filesystem::createWorld();
    std::shared_ptr<State::PlayerTurnState> tempState = {std::make_shared<State::PlayerTurnState> (world)};
    State::addState(tempState);
    int frameRate = 0;
    int startTime = 0;

    try
    {
        for (;;)
        {
            startTime = SDL_GetTicks();

            processInput(State::getCurrentState());
            State::getCurrentState()->update();
            State::getCurrentState()->draw();
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

void processInput(std::shared_ptr<State::State> state)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type)
        {
            case SDL_MOUSEMOTION:
                state->mouseMoved(event.motion.x, event.motion.y);
                break;

            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        state->selectButtonPressed();
                        break;

                    case SDL_BUTTON_RIGHT:
                        state->backButtonPressed();
                        break;
                }
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_DOWN:
                        state->moveDownPressed();
                        break;

                    case SDLK_LEFT:
                        state->moveLeftPressed();
                        break;

                    case SDLK_RIGHT:
                        state->moveRightPressed();
                        break;

                    case SDLK_UP:
                        state->moveUpPressed();
                        break;

                    case SDLK_z:
                        state->selectButtonPressed();
                        break;

                    case SDLK_x:
                        state->backButtonPressed();
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
    Audio::cleanup();

    // The GUI cleanup function also cleans up SDL in general. Should
    // split that up so GUI::cleanup only cleans up the GUI.
    GUI::cleanup();
}

#ifdef _WIN32
    // VS Windows applications need WinMain as an entry point
    int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
    {
        return main();
    }
#endif
