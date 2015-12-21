#include "catch.hpp"

#include "../src/State/GameplayState.h"
#include "../src/State/PokemonSelectedState.h"
#include "../src/State/StateStack.h"


namespace State
{

class TestPokemonSelectedState: public PokemonSelectedState
{
public:
    TestPokemonSelectedState()
    {
        _cursorPos = new Utility::Point(0, 0);
        _map = new std::vector<std::vector<Gameplay::Tile>>();
        for (int i = 0; i < 2; i++)
        {
            std::vector<Gameplay::Tile> column;
            for (int j = 0; j < 2; j++)
            {
                column.push_back(Gameplay::Tile());
            };
            _map->push_back(column);
        }
    };

    ~TestPokemonSelectedState()
    {
        delete _cursorPos;
    };

    Utility::Point* getCursorPos() {return _cursorPos;};
    void setPosition(Utility::Point pos) {*_cursorPos = pos;};
};

// TODO: Test when passed a map with no tiles
TEST_CASE("Testing the PokemonSelectedState state")
{
    std::shared_ptr<TestPokemonSelectedState> pokemonSelectedState = {std::make_shared<TestPokemonSelectedState>()};

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

    SECTION("Testing cursor downward movement")
    {
        Utility::Point* cursorPos = pokemonSelectedState->getCursorPos();
        REQUIRE(cursorPos->y == 0);
        pokemonSelectedState->moveDownPressed();
        REQUIRE(cursorPos->y == 1);
    }

    SECTION("Testing cursor downward movement into a wall")
    {
        Utility::Point* cursorPos = pokemonSelectedState->getCursorPos();
        pokemonSelectedState->setPosition(Utility::Point(0, 1));
        REQUIRE(cursorPos->y == 1);
        pokemonSelectedState->moveDownPressed();
        REQUIRE(cursorPos->y == 1);
    }

    SECTION("Testing cursor leftward movement")
    {
        Utility::Point* cursorPos = pokemonSelectedState->getCursorPos();
        pokemonSelectedState->setPosition(Utility::Point(1, 0));
        REQUIRE(cursorPos->x == 1);
        pokemonSelectedState->moveLeftPressed();
        REQUIRE(cursorPos->x == 0);
    }

    SECTION("Testing cursor leftward movement into a wall")
    {
        Utility::Point* cursorPos = pokemonSelectedState->getCursorPos();
        REQUIRE(cursorPos->x == 0);
        pokemonSelectedState->moveLeftPressed();
        REQUIRE(cursorPos->x == 0);
    }

    SECTION("Testing cursor rightward movement")
    {
        Utility::Point* cursorPos = pokemonSelectedState->getCursorPos();
        REQUIRE(cursorPos->x == 0);
        pokemonSelectedState->moveRightPressed();
        REQUIRE(cursorPos->x == 1);
    }

    SECTION("Testing cursor rightward movement into a wall")
    {
        Utility::Point* cursorPos = pokemonSelectedState->getCursorPos();
        pokemonSelectedState->setPosition(Utility::Point(1, 0));
        REQUIRE(cursorPos->x == 1);
        pokemonSelectedState->moveRightPressed();
        REQUIRE(cursorPos->x == 1);
    }

    SECTION("Testing cursor upward movement")
    {
        Utility::Point* cursorPos = pokemonSelectedState->getCursorPos();
        pokemonSelectedState->setPosition(Utility::Point(0, 1));
        REQUIRE(cursorPos->y == 1);
        pokemonSelectedState->moveUpPressed();
        REQUIRE(cursorPos->y == 0);
    }

    SECTION("Testing cursor upward movement into a wall")
    {
        Utility::Point* cursorPos = pokemonSelectedState->getCursorPos();
        REQUIRE(cursorPos->y == 0);
        pokemonSelectedState->moveUpPressed();
        REQUIRE(cursorPos->y == 0);
    }
}


}