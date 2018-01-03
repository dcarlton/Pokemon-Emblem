#include "../Gameplay/AllianceEnum.h"
#include "../Audio/DJ.h"
#include "Controller/MoveUtils.h"
#include "PlayerTurnState.h"
#include "PokemonSelectedState.h"
#include "StateStack.h"
#include "../Audio/TrackList.h"

#include "../Filesystem/Maps.h"

/*
Generic constructor that initializes a default world
and starts the testing level.
*/
State::PlayerTurnState::PlayerTurnState()
{
    _world = std::make_shared<Gameplay::World>();
    Audio::playMusic(Audio::Music::Music);
}

/*
Constuctor that takes an existing world
*/
State::PlayerTurnState::PlayerTurnState(std::shared_ptr<Gameplay::World> world)
{
    _world = world;
    _world->onStartPlayerTurn();
}

void State::PlayerTurnState::draw()
{
    _world->drawWorld();
}

// Called when the mouse moves to move the cursor wherever the mouse is.
// If the mouse is in the left third of the far left tile, top third of the
// highest tile, etc. then the camera should be moved.
// x and y are the position of mouse on the screen in pixels.
void State::PlayerTurnState::mouseMoved(int x, int y)
{
    Utility::Point newCursorPos = GUI::setCursorFromMouse(x, y, _world->getMapSize());
    _world->setCursorPos(newCursorPos);
}

void State::PlayerTurnState::moveDownPressed()
{
    _world->moveCursorDown();
}

void State::PlayerTurnState::moveLeftPressed()
{
    _world->moveCursorLeft();
}

void State::PlayerTurnState::moveRightPressed()
{
    _world->moveCursorRight();
}

void State::PlayerTurnState::moveUpPressed()
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
void State::PlayerTurnState::selectButtonPressed()
{
    std::shared_ptr<Gameplay::Pokemon> pokemonToSelect = _world->getPokemonUnderCursor();
    if (pokemonToSelect != NULL &&
        !pokemonToSelect->hasMoved &&
        pokemonToSelect->alliance == Gameplay::AllianceEnum::Player)
    {
        addState({std::make_shared<PokemonSelectedState> (this, _world)});
    }
}

void State::PlayerTurnState::update()
{
}
