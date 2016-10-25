#include "../EnemyTurnState.h"
#include "PokemonUtils.h"


void State::Controller::endPokemonsTurn(std::shared_ptr<Gameplay::Pokemon> pokemon, std::shared_ptr<Gameplay::World> world)
{
	pokemon->hasMoved = true;
	if (world->hasAllPlayerPokemonMoved())
	{
		world->resetWhetherPlayerPokemonHaveMoved();
		resetState(std::make_shared<EnemyTurnState>(world));
	}
	else
	{
		resetState();
	}
}