#include <algorithm>
#include <array>
#include <queue>

#include "../Gameplay/Battle.h"
#include "EnemyTurnState.h"
#include "../Gameplay/Move.h"
#include "PlayerTurnState.h"
#include "../Gameplay/Pokemon.h"
#include "StateStack.h"


State::EnemyTurnState::AttackPlan::AttackPlan(Gameplay::Move& move, std::vector<std::vector<Utility::Point>> movementPaths, Utility::Point targetPosition)
    : move(move), movementPaths(movementPaths), targetPosition(targetPosition)
{
}


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

// This creates a map where, for each point, we calculate how far away it is from the starting position.
// It currently does not account for terrain or enemy Pokemon (TODO: do that).
// If we are attacking, we should account for long range moves, include spaces a long range move attacks through,
// and stop when outside of the Pokemon's range.
// If we aren't attacking, we shouldn't care about movement range, only include spaces the Pokemon could move through,
// and keep going when outside the Pokemon's range, so it can move toward opponent's outside its range.
std::vector<std::vector<State::EnemyTurnState::PathInfo>> State::EnemyTurnState::createDistanceMap(Utility::Point startPos, bool isAttacking)
{
    Utility::Point mapSize = _world->getMapSize();
    std::shared_ptr<Gameplay::Pokemon> pokemon = _world->getPokemonFromPosition(startPos);
    std::array<std::shared_ptr<Gameplay::Move>, 4> moves = pokemon->moves;
    int numMoves = pokemon->getNumMoves();
    uint32 movementRange = pokemon->stats.getMovementRange();

    unsigned int maxRange = 0;
    for (int i = 0; i < numMoves; i++)
    {
        maxRange = std::max(maxRange, moves[i]->getRange());
    }
    maxRange += movementRange;

    std::vector<std::vector<PathInfo>> map;
    for (uint32 x = 0; x < mapSize.x; x++)
    {
        std::vector<PathInfo> column;
        for (uint32 y = 0; y < mapSize.y; y++)
        {
            column.push_back(PathInfo(10000, std::vector<Utility::Point>()));
        }
        map.push_back(column);
    }
    map[startPos.x][startPos.y].first = 0;

    // For each position on the map, we need to check it, while
    // also tracking the info of the previous position to build up
    // a path on how to move there.
    typedef Utility::Tuple<Utility::Point, PathInfo> PointToCheckInfo;
    std::queue<PointToCheckInfo> pointsToCheck;

    // NOTE: That vector of points is the spaces to move to reach that point, possibly flying over terrain for long range attacks
    // That includes the spaces a long range move will pass through, just to be clear.
    // If we don't stop at max range, it will only include the spaces we move and attack through.
    // There may also be an ally in each space.
    PathInfo initPointInfo = PathInfo(0, std::vector<Utility::Point>());
    pointsToCheck.push(PointToCheckInfo(Utility::Point(startPos.x - 1, startPos.y), initPointInfo));
    pointsToCheck.push(PointToCheckInfo(Utility::Point(startPos.x + 1, startPos.y), initPointInfo));
    pointsToCheck.push(PointToCheckInfo(Utility::Point(startPos.x, startPos.y - 1), initPointInfo));
    pointsToCheck.push(PointToCheckInfo(Utility::Point(startPos.x, startPos.y + 1), initPointInfo));

    while (!pointsToCheck.empty())
    {
        Utility::Point currentPoint = pointsToCheck.front().first;
        PathInfo lastPointInfo = pointsToCheck.front().second;
        pointsToCheck.pop();

        if (mapSize.contains(currentPoint))
        {
            int x = currentPoint.x;
            int y = currentPoint.y;
            uint32 oldDistance = map[x][y].first;
            
            int terrain = 1; // When implementing terrain slowing you down, add it here.
            uint32 newDistance = isAttacking && lastPointInfo.first + terrain > movementRange ? std::max(lastPointInfo.first, movementRange) + 1 : lastPointInfo.first + terrain;

            if (newDistance < oldDistance && (!isAttacking || newDistance <= maxRange))
            {
                map[x][y].first = newDistance;
                map[x][y].second = std::vector<Utility::Point>(lastPointInfo.second);

                // If we're attacking, always add this point so we can see where the attack goes through.
                // If not, then we only need the point if we can move to it.
                if (isAttacking || newDistance <= movementRange)
                {
                    map[x][y].second.push_back(currentPoint);
                }

                // TODO: Compress
                pointsToCheck.push(PointToCheckInfo(Utility::Point(currentPoint.x - 1, currentPoint.y), map[x][y]));
                pointsToCheck.push(PointToCheckInfo(Utility::Point(currentPoint.x + 1, currentPoint.y), map[x][y]));
                pointsToCheck.push(PointToCheckInfo(Utility::Point(currentPoint.x, currentPoint.y - 1), map[x][y]));
                pointsToCheck.push(PointToCheckInfo(Utility::Point(currentPoint.x, currentPoint.y + 1), map[x][y]));
            }
        }
    }

    return map;
}

void State::EnemyTurnState::draw()
{
    _world->drawWorld();
}

std::vector<Utility::Point> State::EnemyTurnState::findPathToNearestOpponent(Utility::Point startPos)
{
    Gameplay::AllianceEnum attackerAlliance = _world->getPokemonFromPosition(startPos)->alliance;
    Utility::Point closestOpponent;
    uint32 distanceToClosestOpponent = 10000;
    std::vector<std::vector<PathInfo>> map = createDistanceMap(startPos, false);

    for (uint32 x = 0; x < map.size(); x++)
    {
        for (uint32 y = 0; y < map[0].size(); y++)
        {
            Utility::Point currentPos = Utility::Point(x, y);
            std::shared_ptr<Gameplay::Pokemon> currentPokemon = _world->getPokemonFromPosition(currentPos);
            if (currentPokemon != nullptr &&
                currentPokemon->alliance != attackerAlliance &&
                map[x][y].first < distanceToClosestOpponent)
            {
                closestOpponent = Utility::Point(x, y);
                distanceToClosestOpponent = map[x][y].first;
            }
        }
    }

    // Assuming getMap for this function will only add spaces you can move to
    // to the movement path
    return map[closestOpponent.x][closestOpponent.y].second;
}

// TODO: Account for Pokemon occupying each space
std::vector<State::EnemyTurnState::AttackPlan> State::EnemyTurnState::findAllPossibleAttackPlans(Utility::Point startPos)
{
    Utility::Point mapSize = _world->getMapSize();
    std::shared_ptr<Gameplay::Pokemon> pokemon = _world->getPokemonFromPosition(startPos);
    std::array<std::shared_ptr<Gameplay::Move>, 4> moves = pokemon->moves;
    int numMoves = pokemon->getNumMoves();
    uint32 moveRange = pokemon->stats.getMovementRange();

    unsigned int maxRange = 0;
    for (int i = 0; i < numMoves; i++)
    {
        maxRange = std::max(maxRange, moves[i]->getRange());
    }
    maxRange += moveRange;

    std::vector<std::vector<PathInfo>> map = createDistanceMap(startPos, true);

    std::vector<AttackPlan> plans;
    for (uint32 x = 0; x < mapSize.x; x++)
    {
        for (uint32 y = 0; y < mapSize.y; y++)
        {
            if (map[x][y].first > maxRange)
            {
                continue;
            }
            
            Utility::Point targetPosition = Utility::Point(x, y);
            std::shared_ptr<Gameplay::Pokemon> targetPokemon = _world->getPokemonFromPosition(targetPosition);
            if (!targetPokemon)
            {
                continue;
            }

            for (int i = 0; i < numMoves; i++)
            {
                std::shared_ptr<Gameplay::Move> move = moves[i];
                if (move->canTarget(pokemon, targetPokemon))
                {
                    // Find all points within range of the target position that can be moved to.
                    // My main concern is if we just pick one at random, it could be
                    // a space we can't move to because another Pokemon is on it.
                    // Spaces with Pokemon on them can't be ignored though because you
                    // can move through spaces with allied Pokemon on them.
                    std::vector<std::vector<Utility::Point>> movementPaths;
                    std::vector<Utility::Point> nearbyPoints = targetPosition.getPointsWithinDistance(move->getRange());
                    for (uint32 j = 0; j < nearbyPoints.size(); j++)
                    {
                        Utility::Point point = nearbyPoints[j];
                        if (map[point.x][point.y].first > moveRange || _world->getPokemonFromPosition(point))
                        {
                            continue;
                        }

                        movementPaths.push_back(map[point.x][point.y].second);
                    }

                    if (!movementPaths.empty())
                    {
                        plans.push_back(AttackPlan(*move, movementPaths, targetPosition));
                    }
                }
            }
        }
    }

    return plans;
}

bool State::EnemyTurnState::moveAlongPath(Utility::Point startingPosition, std::vector<Utility::Point> movementPath)
{
    Utility::Point currentPosition = startingPosition;
    for (unsigned int i = 0; i < movementPath.size(); i++)
    {
        // TODO: Boolean flag for passing through allied Pokemon
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
    // TODO: Error checking
    AttackPlan* bestPlan = &attackPlans[0];
    int bestAveragePercentDamage = 0;

    for (unsigned int i = 0; i < attackPlans.size(); i++)
    {
        AttackPlan* currentPlan = &attackPlans[i];
        std::shared_ptr<Gameplay::Pokemon> targetPokemon = _world->getPokemonFromPosition(currentPlan->targetPosition);
        Gameplay::Terrain terrain = _world->getTerrainFromPosition(currentPlan->targetPosition);

        // TODO: What about Growl?
        int damage = currentPlan->move.calculateDamage(pokemon, targetPokemon, terrain);
        int accuracy = currentPlan->move.calculateAccuracy(pokemon, targetPokemon, terrain);
        int percentDamage = damage * accuracy;  // Obviously that's not how much damage it will actually do, but for comparisons it works out.

        if (percentDamage > bestAveragePercentDamage)        
        {
            bestPlan = currentPlan;
            bestAveragePercentDamage = percentDamage;
        }
    }

    return *bestPlan;
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
            std::vector<AttackPlan> possibleAttackPlans = findAllPossibleAttackPlans(position);
            if (!possibleAttackPlans.empty())
            {
                AttackPlan optimalAttackPlan = pickOptimalAttackPlan(pokemon, possibleAttackPlans);
                if (moveAlongPath(position, optimalAttackPlan.movementPaths[0]))
                {
                    Gameplay::fight(_world, optimalAttackPlan.movementPaths[0].back(), optimalAttackPlan.move, optimalAttackPlan.targetPosition);
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