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
    PokemonSelectedState(std::shared_ptr<State> prevState,
                         std::vector<std::vector<Gameplay::Tile>> &map,
                         Utility::Point pos);
    void draw();
    void update();

private:
    Utility::Point _cursorPos = Utility::Point(0, 0);
    std::vector<std::vector<Gameplay::Tile>> _map;
};

}

#endif