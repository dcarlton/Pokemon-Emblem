#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include <vector>

#include "../GUI/GUI.h"
#include "../Gameplay/Pokemon.h"
#include "State.h"
#include "../Gameplay/Terrain.h"


class GUI::Image;
class Point;


namespace State
{

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
    std::vector<Gameplay::Pokemon> allPokemon;
    GUI::Image cursorImage = GUI::getImage(GUI::ImageEnum::GameplayCursor);
    Point cursorPos = Point(0, 0);
    std::vector<std::vector<Gameplay::Terrain>> map;

    void initGenericMap();
};

}

#endif