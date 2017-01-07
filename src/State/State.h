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
    virtual void backButtonPressed() {}
    virtual void mouseMoved(int x, int y) { x; y; }
    virtual void moveDownPressed() {}
    virtual void moveLeftPressed() {}
    virtual void moveRightPressed() {}
    virtual void moveUpPressed() {}
    virtual void selectButtonPressed() {}
	virtual void update() = 0;

protected:
    State* _prevState;
};

}

#endif