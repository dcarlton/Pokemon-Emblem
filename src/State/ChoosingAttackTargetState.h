#ifndef CHOOSINGATTACKTARGETSTATE_H
#define CHOOSINGATTACKTARGETSTATE_H

#include <memory>

#include "../Gameplay/Move.h"
#include "State.h"
#include "../Gameplay/World.h"


namespace State
{

class ChoosingAttackTargetState: public State
{
public:
    ChoosingAttackTargetState();
    ChoosingAttackTargetState(State* prevState, std::shared_ptr<Gameplay::World> world, Gameplay::Move selectedMove);
	void backButtonPressed();
    void draw();
    void mouseMoved(int x, int y);
    void moveDownPressed();
    void moveLeftPressed();
    void moveRightPressed();
    void moveUpPressed();
    void selectButtonPressed();
    void update();

protected:
    Utility::Point _originalPos;
    Gameplay::Move _selectedMove;
    std::shared_ptr<Gameplay::World> _world;
};

}


#endif
