#include <vector>

#include "../Gameplay/Battle.h"
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

std::vector<State::EnemyTurnState::AttackPlan> State::EnemyTurnState::findAllPossibleAttackPlans(Utility::Point position, std::array<std::shared_ptr<Gameplay::Move>, 4> moves, int numMoves)
{
    // TODO: Implement
    position;
    moves;
    numMoves;
    return std::vector<AttackPlan>();
}

std::vector<Utility::Point> State::EnemyTurnState::findPathToNearestOpponent(Utility::Point position)
{
    // TODO: Implement
    position;
    return std::vector<Utility::Point>();
}

bool State::EnemyTurnState::moveAlongPath(Utility::Point startingPosition, std::vector<Utility::Point> movementPath)
{
    Utility::Point currentPosition = startingPosition;
    for (unsigned int i = 0; i < movementPath.size(); i++)
    {
        if (!_world->movePokemon(currentPosition, movementPath[i]))
        {
            return false;
        }
        currentPosition = movementPath[i];
    }

    return true;
}

State::EnemyTurnState::AttackPlan State::EnemyTurnState::pickOptimalAttackPlan(std::shared_ptr<Gameplay::Pokemon> pokemon, std::vector<AttackPlan> attackPlans)
{
    // TODO: Implement
    pokemon;
    return attackPlans[0];
}

// Let the enemies take their turn.
// Needs to be changed when I add animation so the
// enemy turn doesn't happen instantly.
void State::EnemyTurnState::update()
{
    std::vector<Utility::Point> pokemonPositions = _world->getEnemyPokemonPositions();   
    for (uint32 i = 0; i < pokemonPositions.size(); i++)
    {
        Utility::Point position = pokemonPositions[i];
        std::shared_ptr<Gameplay::Pokemon> pokemon = _world->getPokemonFromPosition(position);

        // This boolean should never fail.
        if (!pokemon->hasMoved)
        {
            std::vector<AttackPlan> possibleAttackPlans = findAllPossibleAttackPlans(position, pokemon->moves, pokemon->getNumMoves());
            if (!possibleAttackPlans.empty())
            {
                AttackPlan optimalAttackPlan = pickOptimalAttackPlan(pokemon, possibleAttackPlans);
                if (moveAlongPath(position, optimalAttackPlan.movementPath))
                {
                    Gameplay::fight(_world, optimalAttackPlan.movementPath.back(), optimalAttackPlan.move, optimalAttackPlan.targetPosition);
                }
            }
            else
            {
                std::vector<Utility::Point> movementPath = findPathToNearestOpponent(position);
                moveAlongPath(position, movementPath);
            }
        }
    }

    _world->resetWhetherEnemyPokemonHaveMoved();
    resetState(std::make_shared<PlayerTurnState>(_world));
}



/*
void ThinkingOutLoud()
{
    foreach Pokemon
        Map<Move, Struct<Targets, Vector<Point>>> result = A*(Vector<Moves>);
        foreach move:
            foreach target:
                Calculate (damage done / current health) / accuracy
                Save that move and target off if it is the max

        Move along the spaces to reach the optimal target
        Use the move on the target
}
*/