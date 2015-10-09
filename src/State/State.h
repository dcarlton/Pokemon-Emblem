#ifndef STATE_H
#define STATE_H

class State
{
public:
	virtual void draw() = 0;
    void moveDownPressed() {}
    void moveLeftPressed() {}
    void moveRightPressed() {}
    void moveUpPressed() {}
	virtual void update() = 0;
};

#endif