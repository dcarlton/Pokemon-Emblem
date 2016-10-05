#include <vector>

#include "EnemyTurnState.h"
#include "PlayerTurnState.h"
#include "../Gameplay/Pokemon.h"
#include "StateStack.h"


// Generic constructor needed to inherit from State.
// I doubt we'll need this.
State::EnemyTurnState::EnemyTurnState()
{
    _world = std::make_shared<Gameplay::World>();
}

State::EnemyTurnState::EnemyTurnState(std::shared_ptr<Gameplay::World> world)
{
    _world = world;
}

void State::EnemyTurnState::draw()
{
    _world->drawWorld();
}

void State::EnemyTurnState::update()
{
    std::vector<Utility::Point> pokemonPositions = _world->getEnemyPokemonPositions();   
    for (uint32 i = 0; i < pokemonPositions.size(); i++)
    {
        if (!_world->getPokemonFromPosition(pokemonPositions[i])->hasMoved)
        {
            _world->movePokemon(pokemonPositions[i], Utility::Point(pokemonPositions[i].x + 1, pokemonPositions[i].y));
        }
    }

    _world->resetWhetherEnemyPokemonHaveMoved();
    resetState(std::make_shared<PlayerTurnState>(_world));
}