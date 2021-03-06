#ifndef CHOOSINGMOVESTATE_H
#define CHOOSINGMOVESTATE_H


#include <memory>

#include "../Gameplay/Move.h"
#include "State.h"
#include "../Gameplay/World.h"


namespace State
{

class ChoosingMoveState: public State
{
public:
    ChoosingMoveState(State* prevState, std::shared_ptr<Gameplay::World> world);
    void backButtonPressed();
    void draw();
    void mouseMoved(int x, int y);
    void moveDownPressed();
    void moveLeftPressed();
    void moveRightPressed();
    void moveUpPressed();
    void selectButtonPressed();
    void update();

private:
    unsigned int _menuCursorPos;
    std::shared_ptr<Gameplay::Move> _moves[4];
    unsigned int _numMenuItems;
    std::shared_ptr<Gameplay::World> _world;
};

}

#endif