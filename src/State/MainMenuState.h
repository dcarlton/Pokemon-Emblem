#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "State.h"

class MainMenuState: public State
{
public:
	void draw();
	void processInput();
	void update();
};

#endif