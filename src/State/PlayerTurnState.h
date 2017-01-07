#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include <memory>
#include <vector>

#include "../GUI/GUI.h"
#include "../Gameplay/Pokemon.h"
#include "State.h"
#include "../Gameplay/Tile.h"
#include "../Gameplay/World.h"


class GUI::Image;
class Utility::Point;


namespace State
{

class PlayerTurnState: public State
{
public:
    PlayerTurnState();
    PlayerTurnState(std::shared_ptr<Gameplay::World> world);
    void draw();
    void mouseMoved(int x, int y);
    void moveDownPressed();
    void moveLeftPressed();
    void moveRightPressed();
    void moveUpPressed();
    void selectButtonPressed();
    void update();

protected:
    std::vector<std::vector<Gameplay::Tile>> _map;
    std::shared_ptr<Gameplay::World> _world;
};

}

#endif