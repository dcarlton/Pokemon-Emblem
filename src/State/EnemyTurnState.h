#ifndef ENEMYTURNSTATE_H
#define ENEMYTURNSTATE_H


#include <array>
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

protected:
    struct AttackPlan
    {
        Gameplay::Move &move;
        std::vector<Utility::Point> movementPath;
        Utility::Point targetPosition;
    };

    std::shared_ptr<Gameplay::World> _world;

    std::vector<AttackPlan> findAllPossibleAttackPlans(Utility::Point position, std::array<std::shared_ptr<Gameplay::Move>, 4> moves, int numMoves);
    std::vector<Utility::Point> findPathToNearestOpponent(Utility::Point position);
    bool moveAlongPath(Utility::Point startingPosition, std::vector<Utility::Point> movementPath);
    AttackPlan pickOptimalAttackPlan(std::shared_ptr<Gameplay::Pokemon> pokemon, std::vector<AttackPlan> attackPlans);
};

}

#endif