#include "PokemonSelectedState.h"


State::PokemonSelectedState::PokemonSelectedState(std::shared_ptr<State> prevState,
                                                  std::vector<std::vector<Gameplay::Tile>> &map,
                                                  Utility::Point pos)
{
    _cursorPos = pos;
    _map = map;
    _prevState = prevState;
}

void State::PokemonSelectedState::draw()
{
    _prevState->draw();
}

void State::PokemonSelectedState::update()
{
}