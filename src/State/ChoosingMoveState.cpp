#include "ChoosingAttackTargetState.h"
#include "ChoosingMoveState.h"
#include "../Utility/Log.h"
#include "../Gameplay/Move.h"
#include "StateStack.h"


// Initialize this state for selecting a move to use when attacking.
State::ChoosingMoveState::ChoosingMoveState(State* prevState, std::shared_ptr<Gameplay::World> world)
{
    _menuCursorPos = 0;
    _prevState = prevState;
    _world = world;

    _numMenuItems = _world->getPokemonUnderCursor()->getNumMoves();
    if (_numMenuItems < 1 || _numMenuItems > 4)
    {
        Utility::log("Can't choose a move for this Pokemon, it has no attacks, or too many.");
        exitState();
    }
}

// Called when the user presses the back button.
void State::ChoosingMoveState::backButtonPressed()
{
    exitState();
}

// Called once a frame to draw this state to the screen.
void State::ChoosingMoveState::draw()
{
    // TODO: use a different color to mark which item is selected
	_world->drawWorld();

    std::shared_ptr<Gameplay::Move> *moves = _world->getPokemonUnderCursor()->moves;
	std::vector<std::string> menuItems;
	for (int i = 0; i < 4 && moves[i] != nullptr; i++)
	{
		menuItems.push_back(moves[i]->getName());
	}
	GUI::drawMenu(menuItems, _world->getCursorPos());
}

// Called when the mouse is moved. Sets the menu cursor to whatever item the
// mouse is hovering over.
void State::ChoosingMoveState::mouseMoved(int x, int y)
{
    int newMenuCursorPos = GUI::getMenuItemFromMouse(x, y, _world->getCursorPos(), _numMenuItems);
    if (newMenuCursorPos > -1)
        _menuCursorPos = newMenuCursorPos;
}

// Called when the user presses the down button. Either move the
// cursor to the next item in the menu, or reset it to the top of the
// menu, if it's already at the bottom.
void State::ChoosingMoveState::moveDownPressed()
{
    if ((_menuCursorPos + 1) >= _numMenuItems)
    {
        _menuCursorPos = 0;
    }
    else
    {
        _menuCursorPos++;
    }
}

// Called when the user presses the left button. Does nothing.
void State::ChoosingMoveState::moveLeftPressed()
{
}

// Called when the user presses the right button. Does nothing.
void State::ChoosingMoveState::moveRightPressed()
{
}

// Called when the user presses the up button. Moves the cursor
// up on the list of moves, or if it is already at the top, moves
// the cursor to the bottom of the menu.
void State::ChoosingMoveState::moveUpPressed()
{
    if (_menuCursorPos == 0)
    {
        _menuCursorPos = _numMenuItems - 1;
    }
    else
    {
        _menuCursorPos--;
    }
}

// Called when the user presses the select button.
void State::ChoosingMoveState::selectButtonPressed()
{
    Gameplay::Move selectedMove = *(_world->getPokemonUnderCursor()->moves[_menuCursorPos]);
    addState(std::make_shared<ChoosingAttackTargetState>(this, _world, selectedMove));
}

// Called once a frame.
void State::ChoosingMoveState::update()
{
}