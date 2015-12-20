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

    std::shared_ptr<PokemonSelectedState> pokemonSelectedState = {std::make_shared<PokemonSelectedState>(&gameplayState, map, pos)};

    SECTION("Pressing back when the state stack is down")
    {
        REQUIRE_THROWS_AS(pokemonSelectedState->backButtonPressed(), NoStateException);
    }

    SECTION("Pressing back exits the state")
    {
        addState(pokemonSelectedState);
        REQUIRE(getCurrentState() == pokemonSelectedState);
        pokemonSelectedState->backButtonPressed();
        REQUIRE_THROWS_AS(getCurrentState(), NoStateException);
    }
}


}