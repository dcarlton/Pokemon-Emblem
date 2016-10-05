#ifndef ENEMYTURNSTATE_H
#define ENEMYTURNSTATE_H


#include <memory>

#include "State.h"
#include "../Gameplay/World.h"


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
    std::shared_ptr<Gameplay::World> _world;
};

}

#endif