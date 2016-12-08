#include <exception>
#include <memory>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include <fstream>
#include <sstream>
#include "json.hpp"
#include "SDL.h"

#include "src/Audio/DJ.h"
#include "src/GUI/GUI.h"
#include "src/Utility/Log.h"
#include "src/Filesystem/Options.h"
#include "src/State/PlayerTurnState.h"
#include "src/Utility/Size.h"
#include "src/State/StateStack.h"


class State::State;
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
    GUI::createWindow(Utility::Size(320, 320), "Pokemon Emblem");
}

void gameLoop()
{
    std::shared_ptr<State::PlayerTurnState> tempState = {std::make_shared<State::PlayerTurnState> ()};
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

void test()
{
    std::ifstream infile("../pokedex.json");
    std::stringstream stream;
    stream << infile.rdbuf();
    nlohmann::json j = nlohmann::json::parse(stream.str());

    int test = j["bulbasaur"]["num"];
    test;
}

void processInput(std::shared_ptr<State::State> state)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type)
        {
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
                        test();
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

// VS Windows applications need WinMain as an entry point
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    return main();
}
