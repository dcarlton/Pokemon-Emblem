#ifndef BATTLE_H
#define BATTLE_H


#include <memory>

#include "Pokemon.h"
#include "World.h"


namespace Gameplay
{
    void fight(std::shared_ptr<World> world, Utility::Point attackerPosition, Utility::Point targetPosition);
}

#endif