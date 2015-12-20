#include "catch.hpp"

#include "../src/State/GameplayState.h"
#include "../src/State/PokemonSelectedState.h"
#include "../src/State/StateStack.h"


namespace State
{


TEST_CASE("Testing the PokemonSelectedState state")
{
    GameplayState gameplayState;
    std::vector<std::vector<Gameplay::Tile>> map;
    Utility::Point pos(0, 0);

    PokemonSelectedState pokemonSelectedState(&gameplayState, map, pos);

    SECTION("Pressing back when the state stack is down")
    {
        REQUIRE_THROWS_AS(pokemonSelectedState.backButtonPressed(), NoStateException);
    }
}


}