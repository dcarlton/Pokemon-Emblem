#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include <memory>
#include <vector>

#include "../GUI/GUI.h"
#include "../Gameplay/Pokemon.h"
#include "State.h"
#include "../Gameplay/Tile.h"


class GUI::Image;
class Utility::Point;


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
    void selectButtonPressed();
    void update();

private:
    std::vector<std::shared_ptr<Gameplay::Pokemon>> allPokemon;
    GUI::Image cursorImage = GUI::getImage(GUI::ImageEnum::GameplayCursor);
    Utility::Point cursorPos = Utility::Point(0, 0);
    std::vector<std::vector<Gameplay::Tile>> map;

    void initGenericMap();
};

}

#endif