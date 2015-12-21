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

protected:
    GUI::Image _cursorImage = GUI::getImage(GUI::ImageEnum::GameplayCursor);
    Utility::Point _cursorPos = Utility::Point(0, 0);
    std::vector<std::vector<Gameplay::Tile>> _map;

    void initGenericMap();
};

}

#endif