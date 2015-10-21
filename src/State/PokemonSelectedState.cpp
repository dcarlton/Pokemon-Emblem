#include "../Gameplay/Pokemon.h"
#include "PokemonSelectedState.h"
#include "StateStack.h"


State::PokemonSelectedState::PokemonSelectedState(State* prevState,
                                                  std::vector<std::vector<Gameplay::Tile>>& map,
                                                  Utility::Point& pos)
{
    _cursorPos = &pos;
    _map = &map;
    _prevState = prevState;
    _selectedPos = pos;
}

void State::PokemonSelectedState::backButtonPressed()
{
    exitState();
}

void State::PokemonSelectedState::draw()
{
    _prevState->draw();
}

// TODO: Component or some other way to reuse cursor movement
void State::PokemonSelectedState::moveDownPressed()
{
    if (_cursorPos->y < _map->size() - 1)
        (_cursorPos->y)++;
}

void State::PokemonSelectedState::moveLeftPressed()
{
    if (_cursorPos->x > 0)
        (_cursorPos->x)--;
}

void State::PokemonSelectedState::moveRightPressed()
{
    if (_cursorPos->x < _map->size() - 1)
        (_cursorPos->x)++;
}

void State::PokemonSelectedState::moveUpPressed()
{
    if (_cursorPos->y > 0)
        (_cursorPos->y)--;
}

void State::PokemonSelectedState::selectButtonPressed()
{
    std::shared_ptr<Gameplay::Pokemon> selectedPokemon = (*_map)[_selectedPos.x][_selectedPos.y].pokemon;
    if (selectedPokemon &&
        !(*_map)[_cursorPos->x][_cursorPos->y].pokemon)
    {
        (*_map)[_cursorPos->x][_cursorPos->y].pokemon = selectedPokemon;
        (*_map)[_selectedPos.x][_selectedPos.y].pokemon = nullptr;
    }

    exitState();
}

void State::PokemonSelectedState::update()
{
}