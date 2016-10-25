#include "../EnemyTurnState.h"
#include "PokemonUtils.h"


// End a Pokemon's turn by setting its hasMoved property to true,
// and end the player's turn if all of the player's Pokemon have moved.
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