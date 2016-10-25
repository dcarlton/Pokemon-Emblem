#include <iterator>

#include "ChoosingAttackTargetState.h"
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
	addState(std::make_shared<ChoosingAttackTargetState>(state, state->_world));
}

// Executes the "Wait" command to cause a Pokemon to end it's movement.
// Also, if every Pokemon on the player's team has moved, then switch
// to the enemy turn.
void State::waitAction(PokemonActionState* state)
{
	std::shared_ptr<Gameplay::Pokemon> selectedPokemon = state->_world->getPokemonUnderCursor();
    Controller::endPokemonsTurn(selectedPokemon, state->_world);
}

State::PokemonActionState::PokemonActionState(State* prevState, std::shared_ptr<Gameplay::World> world)
{
	_menuCursorPos = 0;
    _prevState = prevState;
	_world = world;

	initMenuItems();
}

void State::PokemonActionState::backButtonPressed()
{
	exitState();
}

void State::PokemonActionState::draw()
{
	// Next goal: write text in the menu, have a list of menu items which can be scrolled through
	// use a different color to mark which item is selected, have the PokemonSelectedState pass which menu items to have
	_prevState->draw();
	std::vector<std::string> menuItems;
	for (auto iter = _menuTextToAction.begin(); iter != _menuTextToAction.end(); iter++)
	{
		menuItems.push_back(iter->first);
	}
	GUI::drawMenu(menuItems, _world->getCursorPos() * 24);

	// On creation, we need a dictionary of item text to a function that should be called when the item is selected.
	// This class handles moving through the menu, and calling the function when an item is selected.
	// The GUI class should be able to draw a menu given the map position and the list of texts to draw.
}

Utility::Point State::PokemonActionState::getMenuPosition()
{
	return Utility::Point((_world->getCursorPos().x * 24) + 24, _world->getCursorPos().y * 24);
}

void State::PokemonActionState::initMenuItems()
{
	_menuTextToAction["Wait"] = &waitAction;

	std::vector<Utility::Point> pointsInRange =_world->getPointsInRange(_world->getCursorPos(), 1);
	std::vector<std::shared_ptr<Gameplay::Pokemon>> pokemonInRange;
	for (auto iter = pointsInRange.begin(); iter != pointsInRange.end(); iter++)
	{
		std::shared_ptr<Gameplay::Pokemon> pokemon = _world->getPokemonFromPosition(*iter);
		if (pokemon != NULL)
		{
			pokemonInRange.push_back(pokemon);
		}
	}

	if (pokemonInRange.size() > 0)
	{
		_menuTextToAction["Attack"] = &attackAction;
	}
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

void State::PokemonActionState::update()
{

}
