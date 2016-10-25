#ifndef CHOOSINGATTACKTARGETSTATE_H
#define CHOOSINGATTACKTARGETSTATE_H

#include <memory>

#include "State.h"
#include "../Gameplay/World.h"


namespace State
{

class ChoosingAttackTargetState: public State
{
public:
    ChoosingAttackTargetState();
    ChoosingAttackTargetState(State* prevState, std::shared_ptr<Gameplay::World> world);
	void backButtonPressed();
    void draw();
    void moveDownPressed();
    void moveLeftPressed();
    void moveRightPressed();
    void moveUpPressed();
    void selectButtonPressed();
    void update();

protected:
    Utility::Point _originalPos;
    std::shared_ptr<Gameplay::World> _world;
};

}


#endif
