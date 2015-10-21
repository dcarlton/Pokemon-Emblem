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
    PokemonSelectedState(State* prevState,
                         std::vector<std::vector<Gameplay::Tile>>& map,
                         Utility::Point& pos);
    void backButtonPressed();
    void draw();
    void moveDownPressed();
    void moveLeftPressed();
    void moveRightPressed();
    void moveUpPressed();
    void selectButtonPressed();
    void update();

private:
    Utility::Point* _cursorPos;
    std::vector<std::vector<Gameplay::Tile>>* _map;
    Utility::Point _selectedPos = Utility::Point(0, 0);
};

}

#endif