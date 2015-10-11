#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include <vector>

#include "../GUI/GUI.h"
#include "../GUI/Image.h"
#include "../Utility/Point.h"
#include "../Data/Pokemon.h"
#include "State.h"
#include "../Data/Terrain.h"

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
    GUI::Image cursorImage = GUI::getImage(GUI::ImageEnum::GameplayCursor);
    Point cursorPos = Point(0, 0);
    std::vector<std::vector<Terrain>> map;

    void initGenericMap();
};

#endif