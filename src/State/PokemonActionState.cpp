#include "..\Utility\Point.h"
#include "PokemonActionState.h"
#include "StateStack.h"


State::PokemonActionState::PokemonActionState(State* prevState, Utility::Point pokemonPos)
{
	_pokemonPos = pokemonPos;
	_prevState = prevState;
}

void State::PokemonActionState::backButtonPressed()
{
	exitState();
}

void State::PokemonActionState::draw()
{
	_prevState->draw();
	GUI::drawImage(_menuItemImage, getMenuPosition());
}

Utility::Point State::PokemonActionState::getMenuPosition()
{
	return Utility::Point((_pokemonPos.x * 24) + 24, _pokemonPos.y * 24);
}

void State::PokemonActionState::moveDownPressed()
{

}

void State::PokemonActionState::moveUpPressed()
{

}

void State::PokemonActionState::selectButtonPressed()
{

}

void State::PokemonActionState::update()
{

}