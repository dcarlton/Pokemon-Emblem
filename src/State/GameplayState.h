#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include <vector>

#include "State.h"
#include "../../src/Data/Image.h"
#include "../../src/Data/Pokemon.h"
#include "../../src/Data/Terrain.h"
#include "../../src/Utility/GUI.h"
#include "../../src/Utility/Point.h"

class GameplayState: public State
{
public:
    GameplayState();
    void draw();
    void moveDownPressed();
    void moveLeftPressed();
    void moveRightPressed();
    void moveUpPressed();
    void update();

private:
    std::vector<Pokemon> allPokemon;
    SDL_Surface* cursorImage = GUI::getImage(Image::gameplayCursor);
    Point cursorPos = Point(0, 0);
    std::vector<std::vector<Terrain>> map;

    void initGenericMap();
};

#endif