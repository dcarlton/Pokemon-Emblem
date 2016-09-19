#ifndef POKEMONACTIONSTATE_H
#define POKEMONACTIONSTATE_H

#include <memory>
#include <vector>

#include "..\GUI\Image.h"
#include "..\GUI\ImageEnum.h"
#include "../Utility/Point.h"
#include "State.h"
#include "../Gameplay/Tile.h"
#include "../Gameplay/World.h"


namespace State
{

class PokemonActionState: public State
{
public:
    PokemonActionState(State* prevState, std::shared_ptr<Gameplay::World> world);
	void backButtonPressed();
    void draw();
    void moveDownPressed();
    void moveUpPressed();
    void selectButtonPressed();
    void update();

protected:
	GUI::Image _menuItemImage = GUI::getImage(GUI::ImageEnum::MenuItem);
    std::shared_ptr<Gameplay::World> _world;

	Utility::Point getMenuPosition();
};


}


#endif
