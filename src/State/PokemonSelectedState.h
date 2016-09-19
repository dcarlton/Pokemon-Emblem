#ifndef POKEMON_SELECTED_STATE_H
#define POKEMON_SELECTED_STATE_H

#include <memory>
#include <vector>

#include "../Utility/Point.h"
#include "State.h"
#include "../Gameplay/Tile.h"


namespace State
{

class PokemonSelectedState: public State
{
public:
    PokemonSelectedState() {}; // Subclasses need a default constructor
    PokemonSelectedState(State* prevState, std::shared_ptr<Gameplay::World> world);
    void backButtonPressed();
    void draw();
    void moveDownPressed();
    void moveLeftPressed();
    void moveRightPressed();
    void moveUpPressed();
    void selectButtonPressed();
    void update();

protected:
    // A standard pointer is needed here so changes made to _cursorPos
    // also impact the GameplayState's cursor. No, a reference won't work.
    Utility::Point _selectedPos = Utility::Point(0, 0);
    std::shared_ptr<Gameplay::World> _world;
};

}

#endif