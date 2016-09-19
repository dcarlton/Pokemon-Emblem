#include "../Utility/Log.h"
#include "Controller/MoveUtils.h"
#include "../Gameplay/Pokemon.h"
#include "PokemonActionState.h"
#include "PokemonSelectedState.h"
#include "StateStack.h"


State::PokemonSelectedState::PokemonSelectedState(State* prevState, std::shared_ptr<Gameplay::World> world)
{
    _prevState = prevState;
    _selectedPos = world->getCursorPos();
    _world = world;

    Utility::log("Selecting the Pokemon at " + _world->getCursorPos().to_string());
    Utility::log(_world->getPokemonUnderCursor() ? "Pokemon exists" : "Pokemon does not exist");
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
    _world->moveCursorDown();
}

void State::PokemonSelectedState::moveLeftPressed()
{
    _world->moveCursorLeft();
}

void State::PokemonSelectedState::moveRightPressed()
{
    _world->moveCursorRight();
}

void State::PokemonSelectedState::moveUpPressed()
{
    _world->moveCursorUp();
}

/*
 * When a Pokemon has been selected, and the select button is
 * pressed again, this function is called. This brings up the action
 * menu where the selected Pokemon can attack, wait, use items, etc.
 */
void State::PokemonSelectedState::selectButtonPressed()
{
    // TODO: Don't leave this state if the move doesn't work.
    _world->movePokemon(_selectedPos, _world->getCursorPos());
    replaceState(std::make_shared<PokemonActionState>(_prevState, _world));
}

void State::PokemonSelectedState::update()
{
}
