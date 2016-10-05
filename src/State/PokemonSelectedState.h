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
    void moveIfValid();
    void moveLeftPressed();
    void moveRightPressed();
    void moveUpPressed();
    void selectButtonPressed();
    void update();

protected:
    // The original position is where the Pokemon was selected when this state is created.
    // The current Pokemon position is where the Pokemon has been moved to. This is usually,
    // but not always, the same as the world's current cursor position.
    Utility::Point _currentPokemonPos = Utility::Point(0, 0);
    Utility::Point _originalPos = Utility::Point(0, 0);
    std::shared_ptr<Gameplay::World> _world;
};

}

#endif