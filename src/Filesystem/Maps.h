#ifndef MAPS_H
#define MAPS_H

#include <memory>

#include "../Gameplay/World.h"


namespace Filesystem
{

std::shared_ptr<Gameplay::World> CreateWorld();

}


#endif