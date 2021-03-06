#include "../Utility/Log.h"
#include "Controller/MoveUtils.h"
#include "../Gameplay/Pokemon.h"
#include "PokemonActionState.h"
#include "PokemonSelectedState.h"
#include "StateStack.h"


State::PokemonSelectedState::PokemonSelectedState(State* prevState, std::shared_ptr<Gameplay::World> world)
{
    _currentPokemonPos = world->getCursorPos();
    _prevState = prevState;
    _originalPos = _currentPokemonPos;
    _world = world;

    Utility::log("Selecting the Pokemon at " + _world->getCursorPos().to_string());
    Utility::log(_world->getPokemonUnderCursor() ? "Pokemon exists" : "Pokemon does not exist");
}

void State::PokemonSelectedState::backButtonPressed()
{
    _world->movePokemon(_currentPokemonPos, _originalPos);
    exitState();
}

void State::PokemonSelectedState::draw()
{
    _prevState->draw();
}

// Called when the mouse is moved. Move the cursor to the mouse's
// x and y position, if it's within range.
void State::PokemonSelectedState::mouseMoved(int x, int y)
{
    Utility::Point cursorPos = GUI::setCursorFromMouse(x, y, _world->getMapSize());
    _world->setCursorPosIfInRange(_originalPos, cursorPos, _world->getPokemonFromPosition(_currentPokemonPos)->stats.getMovementRange());
    moveIfValid();
}

void State::PokemonSelectedState::moveDownPressed()
{
    _world->moveCursorDownIfInRange(_originalPos, _world->getPokemonFromPosition(_currentPokemonPos)->stats.getMovementRange());
    moveIfValid();
}

// Move the selected Pokemon to the location of the cursor, if possible.
void State::PokemonSelectedState::moveIfValid()
{
    if (_originalPos.distanceFrom(_world->getCursorPos()) <= _world->getPokemonFromPosition(_currentPokemonPos)->stats.getMovementRange() && 
        _world->movePokemon(_currentPokemonPos, _world->getCursorPos()))
    {
       _currentPokemonPos = _world->getCursorPos();
    }
}

void State::PokemonSelectedState::moveLeftPressed()
{
    _world->moveCursorLeftIfInRange(_originalPos, _world->getPokemonFromPosition(_currentPokemonPos)->stats.getMovementRange());
    moveIfValid();
}

void State::PokemonSelectedState::moveRightPressed()
{
    _world->moveCursorRightIfInRange(_originalPos, _world->getPokemonFromPosition(_currentPokemonPos)->stats.getMovementRange());
    moveIfValid();
}

void State::PokemonSelectedState::moveUpPressed()
{
    _world->moveCursorUpIfInRange(_originalPos, _world->getPokemonFromPosition(_currentPokemonPos)->stats.getMovementRange());
    moveIfValid();
}

/*
 * When a Pokemon has been selected, and the select button is
 * pressed again, this function is called. This brings up the action
 * menu where the selected Pokemon can attack, wait, use items, etc.
 */
void State::PokemonSelectedState::selectButtonPressed()
{
    // If the selected Pokemon couldn't be moved to the cursor, then
    // we shouldn't go to the PokemonActionState where the user can
    // attack or finalize their move.
    if (_currentPokemonPos != _world->getCursorPos())
        return;

    addState(std::make_shared<PokemonActionState>(_prevState, _world));
}

void State::PokemonSelectedState::update()
{
}
