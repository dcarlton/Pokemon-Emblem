#include "../Utility/Log.h"
#include "Controller/MoveUtils.h"
#include "../Gameplay/Pokemon.h"
#include "PokemonActionState.h"
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

    Utility::log(_cursorPos->to_string() + ": " + pos.to_string() + ": " + _selectedPos.to_string());
    Utility::log((*_map)[_selectedPos.y][_selectedPos.x].pokemon ? "Pokemon exists" : "Pokemon does not exist");
}

void State::PokemonSelectedState::backButtonPressed()
{
    exitState();
}

void State::PokemonSelectedState::draw()
{
    _prevState->draw();
}

void State::PokemonSelectedState::moveDownPressed()
{
    _cursorPos->y = ::State::Controller::moveDown(_cursorPos->y, _map[0].size() - 1);
}

void State::PokemonSelectedState::moveLeftPressed()
{
    _cursorPos->x = ::State::Controller::moveLeft(_cursorPos->x, 0);
}

void State::PokemonSelectedState::moveRightPressed()
{
    _cursorPos->x = ::State::Controller::moveRight(_cursorPos->x, _map[0].size() - 1);
}

void State::PokemonSelectedState::moveUpPressed()
{
    _cursorPos->y = ::State::Controller::moveUp(_cursorPos->y, 0);
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

	replaceState(std::make_shared<PokemonActionState>(_prevState, *_cursorPos));
}

void State::PokemonSelectedState::update()
{
}