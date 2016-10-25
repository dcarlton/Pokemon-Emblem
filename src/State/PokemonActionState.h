#ifndef POKEMONACTIONSTATE_H
#define POKEMONACTIONSTATE_H

#include <functional>
#include <map>
#include <memory>
#include <vector>

#include "..\GUI\Image.h"
#include "..\GUI\ImageEnum.h"
#include "../Utility/Point.h"
#include "../Gameplay/Pokemon.h"
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

    friend void attackAction(PokemonActionState* state);
    friend void waitAction(PokemonActionState* state);

protected:
    uint32 _menuCursorPos;
	GUI::Image _menuItemImage = GUI::getImage(GUI::ImageEnum::MenuItem);
    std::map<std::string, std::function<void(PokemonActionState*)>> _menuTextToAction;
    Utility::Point _originalPos;
    std::shared_ptr<Gameplay::World> _world;

    void endPokemonsTurn(std::shared_ptr<Gameplay::Pokemon> pokemon);
	Utility::Point getMenuPosition();
    void initMenuItems();
};


}


#endif
