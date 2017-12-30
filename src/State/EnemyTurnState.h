#ifndef ENEMYTURNSTATE_H
#define ENEMYTURNSTATE_H


#include <memory>
#include <vector>

#include "State.h"
// TODO: Forward declare this
#include "../Gameplay/World.h"

class Gameplay::Move;
class Gameplay::Pokemon;


namespace State
{

class EnemyTurnState: public State
{
public:
    EnemyTurnState();
    EnemyTurnState(std::shared_ptr<Gameplay::World> world);
    void draw();
    void update();

    // By all logic this should be protected, but MSBuild 2017
    // thinks that findAllPossibleAttackPlans can't see it because
    // it's protected <_< So blame Microsoft if anything dumb happens.
    struct AttackPlan
    {
        Gameplay::Move &move;
        std::vector<std::vector<Utility::Point>> movementPaths;
        Utility::Point targetPosition;

        AttackPlan(Gameplay::Move& move, std::vector<std::vector<Utility::Point>> movementPaths, Utility::Point targetPosition);
    };

protected:
    std::shared_ptr<Gameplay::World> _world;

    std::vector<AttackPlan> findAllPossibleAttackPlans(Utility::Point position);
    std::vector<Utility::Point> findPathToNearestOpponent(Utility::Point position);
    bool moveAlongPath(Utility::Point startingPosition, std::vector<Utility::Point> movementPath);
    AttackPlan pickOptimalAttackPlan(std::shared_ptr<Gameplay::Pokemon> pokemon, std::vector<AttackPlan> attackPlans);
};

}

#endif