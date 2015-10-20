#ifndef STATE_H
#define STATE_H

#include <memory>

#include "../GUI/GUI.h"

namespace State
{

class State
{
public:
	virtual void draw() = 0;
    virtual void moveDownPressed() {}
    virtual void moveLeftPressed() {}
    virtual void moveRightPressed() {}
    virtual void moveUpPressed() {}
	virtual void update() = 0;

protected:
    std::shared_ptr<State> _prevState;
};

}

#endif