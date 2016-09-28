#include "..\Utility\Point.h"
#include "PokemonActionState.h"
#include "StateStack.h"


State::PokemonActionState::PokemonActionState(State* prevState, std::shared_ptr<Gameplay::World> world)
{
    _prevState = prevState;
	_world = world;
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
	GUI::drawImage(_menuItemImage, getMenuPosition());
}

Utility::Point State::PokemonActionState::getMenuPosition()
{
	return Utility::Point((_world->getCursorPos().x * 24) + 24, _world->getCursorPos().y * 24);
}

void State::PokemonActionState::moveDownPressed()
{

}

void State::PokemonActionState::moveUpPressed()
{

}

/*
 * Called when a Pokemon is selected and the Select button
 * is pressed. When a Pokemon is selected, a menu will appear;
 * this function selects the menu item the user has chosen.
 */
void State::PokemonActionState::selectButtonPressed()
{
    std::shared_ptr<Gameplay::Pokemon> selectedPokemon = _world->getPokemonUnderCursor();
    selectedPokemon->hasMoved = true;
	if (_world->hasAllPlayerPokemonMoved())
	{
		_world->resetWhetherPlayerPokemonHaveMoved();
		// TODO: Give the enemy team a turn.
	}

	resetState();
}

void State::PokemonActionState::update()
{

}
