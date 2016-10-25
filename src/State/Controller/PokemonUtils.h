#ifndef POKEMONUTILS_H
#define POKEMONUTILS_H


#include <memory>

#include "../../Gameplay/Pokemon.h"
#include "../StateStack.h"
#include "../../Gameplay/World.h"

namespace State
{

namespace Controller
{


void endPokemonsTurn(std::shared_ptr<Gameplay::Pokemon> pokemon, std::shared_ptr<Gameplay::World> world);


}
}

#endif