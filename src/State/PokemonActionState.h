#ifndef POKEMONACTIONSTATE_H
#define POKEMONACTIONSTATE_H

#include <memory>

#include "..\GUI\Image.h"
#include "..\GUI\ImageEnum.h"
#include "State.h"
#include "..\Utility\Point.h"


namespace State
{

class PokemonActionState: public State
{
public:
	PokemonActionState(State* prevState, Utility::Point pokemonPos);
	void backButtonPressed();
    void draw();
    void moveDownPressed();
    void moveUpPressed();
    void selectButtonPressed();
    void update();

protected:
	GUI::Image _menuItemImage = GUI::getImage(GUI::ImageEnum::MenuItem);
	Utility::Point _pokemonPos = Utility::Point(0, 0);

	Utility::Point getMenuPosition();
};


}


#endif