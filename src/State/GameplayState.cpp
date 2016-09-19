#include "../Gameplay/AllianceEnum.h"
#include "GameplayState.h"
#include "Controller/MoveUtils.h"
#include "PokemonSelectedState.h"
#include "StateStack.h"


/*
Generic constructor that initializes a default world
and starts the testing level.
*/
State::GameplayState::GameplayState()
{
    _world = std::make_shared<Gameplay::World>();
}

/*
Constuctor that takes an existing world
*/
State::GameplayState::GameplayState(std::shared_ptr<Gameplay::World> world)
{
    _world = world;
}

void State::GameplayState::draw()
{
    _world->drawWorld();
}

void State::GameplayState::moveDownPressed()
{
    _world->moveCursorDown();
}

void State::GameplayState::moveLeftPressed()
{
    _world->moveCursorLeft();
}

void State::GameplayState::moveRightPressed()
{
    _world->moveCursorRight();
}

void State::GameplayState::moveUpPressed()
{
    _world->moveCursorUp();
}

/*
 * This function is called during the user's turn when the user presses
 * the Select button. If the user has the cursor over a Pokemon on their
 * team that has not yet moved, that Pokemon is selected to be moved.
 * Otherwise, it should (TODO) pop up a menu with options like ending your
 * turn, or accessing the options menu.
 */
void State::GameplayState::selectButtonPressed()
{
    std::shared_ptr<Gameplay::Pokemon> pokemonToSelect = _world->getPokemonUnderCursor();
    if (pokemonToSelect != NULL &&
        !pokemonToSelect->hasMoved &&
        pokemonToSelect->alliance == Gameplay::AllianceEnum::Player)
    {
        addState({std::make_shared<PokemonSelectedState> (this, _world)});
    }
}

void State::GameplayState::update()
{
}
