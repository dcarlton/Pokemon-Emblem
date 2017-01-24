#include <iterator>

#include "ChoosingMoveState.h"
#include "EnemyTurnState.h"
#include "..\Utility\Point.h"
#include "PokemonActionState.h"
#include "Controller/PokemonUtils.h"
#include "StateStack.h"



// There will be many functions defined as friends of this state.
// This is because I'm storing info on each menu item as a mapping
// of strings to functions. However, only non-member functions can be saved
// for some asinine reason. Thus, for each option in the menu that the
// user might pick, we need a non-member function which can still
// access the normal private variables.

// Executes the "Attack" command to cause a Pokemon to attack another Pokemon
// in range.
void State::attackAction(PokemonActionState* state)
{
	addState(std::make_shared<ChoosingMoveState>(state, state->_world));
}

// Executes the "Wait" command to cause a Pokemon to end it's movement.
// Also, if every Pokemon on the player's team has moved, then switch
// to the enemy turn.
void State::waitAction(PokemonActionState* state)
{
	std::shared_ptr<Gameplay::Pokemon> selectedPokemon = state->_world->getPokemonUnderCursor();
    Controller::endPokemonsTurn(selectedPokemon, state->_world);
}

// Initialize default values for selecting what action a Pokemon should
// do from a menu.
State::PokemonActionState::PokemonActionState(State* prevState, std::shared_ptr<Gameplay::World> world)
{
	_menuCursorPos = 0;
	_originalPos = world->getCursorPos();
    _prevState = prevState;
	_world = world;

	initMenuItems();
}

// Called when the back button is pressed to stop choosing an action
// and return to choosing where the Pokemon should move.
void State::PokemonActionState::backButtonPressed()
{
	exitState();
}

// Draw the map, then the menu.
void State::PokemonActionState::draw()
{
	// TODO: use a different color to mark which item is selected
	_prevState->draw();
	std::vector<std::string> menuItems;
	for (auto iter = _menuTextToAction.begin(); iter != _menuTextToAction.end(); iter++)
	{
		menuItems.push_back(iter->first);
	}
	GUI::drawMenu(menuItems, _originalPos);
}

// Create the items in the menu.
void State::PokemonActionState::initMenuItems()
{
	_menuTextToAction["Wait"] = &waitAction;

	if (isEnemyInRange())
	{
		_menuTextToAction["Attack"] = &attackAction;
	}
}

// Returns true if the selected Pokemon has an enemy within
// range of one of its attacks.
bool State::PokemonActionState::isEnemyInRange()
{
	unsigned int maxRange = _world->getPokemonUnderCursor()->getMaxRange();
	std::vector<Utility::Point> pointsInRange =_world->getPointsInRange(_world->getCursorPos(), maxRange);
	std::vector<std::shared_ptr<Gameplay::Pokemon>> pokemonInRange;
	
	for (auto iter = pointsInRange.begin(); iter != pointsInRange.end(); iter++)
	{
		std::shared_ptr<Gameplay::Pokemon> pokemon = _world->getPokemonFromPosition(*iter);
		if (pokemon != NULL)
		{
			pokemonInRange.push_back(pokemon);
		}
	}

	return pokemonInRange.size() > 0;
}

// Called when the mouse moves. Set the menu cursor to the mouse's location.
void State::PokemonActionState::mouseMoved(int x, int y)
{
	int newMenuCursorPos = GUI::getMenuItemFromMouse(x, y, _originalPos, _menuTextToAction.size());
	if (newMenuCursorPos > -1)
		_menuCursorPos = newMenuCursorPos;
}

// Called when the user presses a button to move the menu cursor downward.
void State::PokemonActionState::moveDownPressed()
{
	if (_menuCursorPos < (_menuTextToAction.size() - 1))
		_menuCursorPos++;
}

// Called when the user presses a button to move the menu cursor upward.
void State::PokemonActionState::moveUpPressed()
{
	if (_menuCursorPos > 0)
		_menuCursorPos--;
}

/*
 * Called when a Pokemon is selected and the Select button
 * is pressed. When a Pokemon is selected, a menu will appear;
 * this function selects the menu item the user has chosen.
 */
void State::PokemonActionState::selectButtonPressed()
{
	auto iter = _menuTextToAction.begin();
	std::advance(iter, _menuCursorPos);
	iter->second(this);
}

// Called every frame.
void State::PokemonActionState::update()
{

}
