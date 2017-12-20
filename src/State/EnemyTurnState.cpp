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

// TODO: Account for Pokemon occupying each space
// Possibly by just returning the table and allowing for more complex calculations elsewhere
psuedocode round3Baybeeeeeeeeeee(Utility::Point startPos, moves[4], numMoves, speed, attackingAlliance)
{
    maxRange = 0
    foreach (move)
        maxRange = max(maxRange, move.range)

    mapSize = world.mapSize
    vector<vector<Tuple>> map;
    map.initializeEverything(Tuple(10000, vector<Point>()))
    map[startPos.x][startPos.y] = 0;

    queue<Tuple> pointsToCheck
    // NOTE: That vector of points is the spaces to move to reach that point, possibly flying over terrain for long range attacks
    // There may also be an ally in each space
    lastPointInfo = Tuple(0, vector<Point>())
    foreach (first points to check)
        queue.add(Tuple(pointToCheck, lastPointInfo))

    while (queue not empty)
    {
        temp = queue.pop
        currentPoint = temp.first
        lastPointInfo = temp.second
        if its on the map
            oldDistance = map[x][y].first;
            newDistance = lastPointInfo.first + terrain > speed ? lastPointInfo.first + 1 : lastPointInfo.first + terrain

            if lastPointInfo.first + terrain < speed
                newDistance = that
            elif terrain is impassible by moves
                continue
            else
                newDistance = lastPointInfo.first + 1

            if new < old and new < maxRange
                map[x][y].first = new
                map[x][y].second = lastPointInfo.second + currentPoint
                
                foreach adjacent point
                    queue.add(Tuple(adjacentPoint, map[x][y]))
    }


    plans
    for every space in the map
        if map[x][y].first > maxRange
            continue

        if no Pokemon at x, y
            continue

        foreach move
            if Pokemon has same alliance and move targets allies and its not the attacker
            or if Pokemon has different alliance and move targets enemies
            or if move hits self and Pokemon is self
                AttackPlan;
                plan.move = &move
                foreach space(tempX, tempY) within range of the target:
                    if pokemon cant move there in one turn or there is another Pokemon in that space
                        continue
                    plan.movementPaths.add(map[tempX][tempY].second.remove_from_end(distanceFromTarget))
                plan.targetPosition = x, y
                plans.add(plan)

    return plans
}

std::vector<AttackPlan> State::EnemyTurnState::findAllPossibleAttackPlans(Utility::Point startingPosition, std::array<Gameplay::Move, 4> moves, int numMoves)
{
    // TODO: Compress everything
    // TODO(future): Should account for a Pokemon's movement as well
    // as the move range, since moves aren't slowed by terrain.
    unsigned int maxRange = 0;
    for (int i = 0; i < numMoves; i++)
    {
        maxRange = std::max(maxRange, moves[i].getRange());
    }

    Utility::Point mapSize = _world->getMapSize();
    typedef std::tuple<int, std::vector<Utility::Point>> DistanceInfo;
    // TODO: Replace C++'s awful Tuple class with my own using Templates
    std::vector<std::vector<DistanceInfo> mapOfDistances(mapSize.x, std::vector<int>(mapSize.y, DistanceInfo(10000, std::vector<Utility::Point>())));
    std::get<0>(mapOfDistances[startingPosition.x][startingPosition.y]) = 0;

    // // TODO: Reuse DistanceInfo typedef for PointInfo
    struct PointInfo
    {
        Utility::Point point;
        int distanceOfLastPoint;

        PointInfo(int x, int y, int distanceOfLastPoint)
        {
            point = Utility::Point(x, y);
            this->distanceOfLastPoint = distanceOfLastPoint;
        }
    };

    std::queue<PointInfo> pointsToCheck;
    pointsToCheck.push(PointInfo(startingPosition.x + 1, startingPosition.y, 0));
    pointsToCheck.push(PointInfo(startingPosition.x - 1, startingPosition.y, 0));
    pointsToCheck.push(PointInfo(startingPosition.x, startingPosition.y + 1, 0));
    pointsToCheck.push(PointInfo(startingPosition.x, startingPosition.y - 1, 0));


    while (!pointsToCheck.empty())
    {
        PointInfo currentPointInfo = pointsToCheck.pop();
        if (currentPointInfo.x < 0 || currentPointInfo.x >= mapSize.x || currentPointInfo.y < 0 || currentPointInfo.y >= mapSize.y)
        {
            continue;
        }

        int newDistance = currentPointInfo.distanceOfLastPoint + 1;
        int& oldDistance = std::get<0>(mapOfDistances[currentPointInfo.point.x][currentPointInfo.point.y]);
        if (newDistance < oldDistance && newDistance <= maxRange)
        {
            oldDistance = newDistance;
            pointsToCheck.push(PointInfo(currentPointInfo.point.x + 1, currentPointInfo.point.y, newDistance));
            pointsToCheck.push(PointInfo(currentPointInfo.point.x - 1, currentPointInfo.point.y, newDistance));
            pointsToCheck.push(PointInfo(currentPointInfo.point.x, currentPointInfo.point.y + 1, newDistance));
            pointsToCheck.push(PointInfo(currentPointInfo.point.x, currentPointInfo.point.y - 1, newDistance));
        }
    }


    Gameplay::AllianceEnum attackingAlliance = _world->getPokemonUnderCursor()->alliance;
    std::vector<AttackPlan> attackPlans;
    for (int x = 0; x < mapSize.x; x++)
    {
        for (int y = 0; y < mapSize.y; y++)
        {
            if (std::get<0>(mapOfDistances[x][y]) > maxRange)
            {
                continue;
            }

            Utility::Point position = Utility::Point(x, y);
            std::shared_ptr<Gameplay::Pokemon> pokemon = _world->getPokemonFromPosition(position);
            if (pokemon == nullptr)
            {
                continue;
            }

            int distance = position.distanceFrom(startingPosition);
            for (int i = 0; i < numMoves; i++)
            {
                // TODO: For all that is good in the world, make a function out of this.
                if (moves[i].getTarget & Gameplay::TARGET::ALLY &&
                    pokemon->alliance == attackingAlliance &&
                    position != startingPosition)
                {
                    AttackPlan plan;
                    plan.move = &moves[i];
                    plan.movementPath = std::get<1>(mapOfDistances[position.x][position.y]);
                    plan.targetPosition = position;
                    attackPlans.push_back(plan);
                }
                else if (moves[i].getTarget & Gameplay::TARGET::ENEMY &&
                         pokemon->alliance != attackingAlliance)
                {
                    AttackPlan plan;
                    plan.move = &moves[i];
                    plan.movementPath = std::get<1>(mapOfDistances[position.x][position.y]);
                    plan.targetPosition = position;
                    attackPlans.push_back(plan);
                }
                else if (moves[i].getTarget & Gameplay::TARGET::SELF &&
                    position == startingPosition)
                {
                    AttackPlan plan;
                    plan.move = &moves[i];
                    plan.movementPath = std::get<1>(mapOfDistances[position.x][position.y]);
                    plan.targetPosition = position;
                    attackPlans.push_back(plan);
                }
            }
        }
    }

    return attackPlans;
}

/*
struct thingy
{
    std::vector<std::shared_ptr<Gameplay::Pokemon>> targetsInRange;
    unsigned int range;
    unsigned int targetAllianceFlag;
};

void State::EnemyTurnState::pathfinding(Utility::Point position, std::vector<&thingy> thingies)
{
    // TODO: Oh my gosh this code is ugly and unclear.
    unsigned int maxRange = 0;
    for (int i = 0; i < thingies.size(); i++)
    {
        maxRange = std::max(maxRange, thingies[i].range);
    }
    maxRange += _world->getPokemonUnderCursor()->stats.getSpeed();

    Utility::Point mapSize = _world->getMapSize();
    std::vector<std::vector<int>> map(mapSize.x, std::vector<int>(mapSize.y, 10000));
    map[position.x][position.y] = 0;
    for (int i = 0; i < thingies.size(); i++)
    {
        if (thingies[i].targetAllianceFlag & Gameplay::TARGET::SELF)
        {
            // TODO: Error checking just in case targetsInRange isn't created yet.
            // Which might not be possible?
            thingies[i].targetsInRange.push_back(_world->getPokemonUnderCursor());
        }
    }


    // Make a queue of points on a map to check, plus how much speed
    // it took to move that far.
    struct PointInfo
    {
        Utility::Point point;
        int distance;

        PointInfo(Utility::Point point, int distance)
        {
            this->point = point;
            this->distance = distance;
        }
    };
    std::queue<PointInfo> pointsToCheck;
    pointsToCheck.push(PointInfo(Utility::Point(position.x + 1, position.y), 0));
    pointsToCheck.push(PointInfo(Utility::Point(position.x - 1, position.y), 0));
    pointsToCheck.push(PointInfo(Utility::Point(position.x, position.y + 1), 0));
    pointsToCheck.push(PointInfo(Utility::Point(position.x, position.y - 1), 0));

    while (!pointsToCheck.empty())
    {
        PointInfo pointInfo = pointsToCheck.pop();
        Point point =  pointInfo.point;
        if (point.x < 0 || point.x >= mapSize.x || point.y < 0 || point.y >= mapSize.y)
        {
            continue;
        }

        // TODO: Terrain movement replaces that 1
        int newDistance = pointInfo.distance + 1;
        if (newDistance < map[point.x][point.y] && newDistance <= maxRange)
        {
            map[point.x][point.y] = newDistance;
            pointsToCheck.push(PointInfo(Utility::Point(point.x + 1, point.y), 0));
            pointsToCheck.push(PointInfo(Utility::Point(point.x - 1, point.y), 0));
            pointsToCheck.push(PointInfo(Utility::Point(point.x, point.y + 1), 0));
            pointsToCheck.push(PointInfo(Utility::Point(point.x, point.y - 1), 0));
        }
    }


    // TODO: Build up the list of Pokemon in range,
    // and the movement path to reach them.
}*/

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