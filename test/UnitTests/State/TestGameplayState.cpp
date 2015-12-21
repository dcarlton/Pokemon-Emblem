#include "catch.hpp"

#include "../src/State/GameplayState.h"
#include "../src/State/StateStack.h"


namespace State
{

class TestGameplayState: public GameplayState
{
public:
    TestGameplayState() {_map.resize(2); _map[0].resize(2);};
    bool checkCursorPos(Utility::Point pos) {return _cursorPos == pos;};
    void setPosition(Utility::Point pos) {_cursorPos = pos;};
};

// TODO: Test when passed a map with no tiles
TEST_CASE("Testing the GameplayState state")
{
    std::shared_ptr<TestGameplayState> gameplayState = {std::make_shared<TestGameplayState>()};

    SECTION("Testing cursor downward movement")
    {
        REQUIRE(gameplayState->checkCursorPos(Utility::Point(0, 0)));
        gameplayState->moveDownPressed();
        REQUIRE(gameplayState->checkCursorPos(Utility::Point(0, 1)));
    }

    SECTION("Testing cursor downward movement into a wall")
    {
        gameplayState->setPosition(Utility::Point(0, 1));
        REQUIRE(gameplayState->checkCursorPos(Utility::Point(0, 1)));
        gameplayState->moveDownPressed();
        REQUIRE(gameplayState->checkCursorPos(Utility::Point(0, 1)));
    }

    SECTION("Testing cursor leftward movement")
    {
        gameplayState->setPosition(Utility::Point(1, 0));
        REQUIRE(gameplayState->checkCursorPos(Utility::Point(1, 0)));
        gameplayState->moveLeftPressed();
        REQUIRE(gameplayState->checkCursorPos(Utility::Point(0, 0)));
    }

    SECTION("Testing cursor leftward movement into a wall")
    {
        REQUIRE(gameplayState->checkCursorPos(Utility::Point(0, 0)));
        gameplayState->moveLeftPressed();
        REQUIRE(gameplayState->checkCursorPos(Utility::Point(0, 0)));
    }

    SECTION("Testing cursor rightward movement")
    {
        REQUIRE(gameplayState->checkCursorPos(Utility::Point(0, 0)));
        gameplayState->moveRightPressed();
        REQUIRE(gameplayState->checkCursorPos(Utility::Point(1, 0)));
    }

    SECTION("Testing cursor rightward movement into a wall")
    {
        gameplayState->setPosition(Utility::Point(1, 0));
        REQUIRE(gameplayState->checkCursorPos(Utility::Point(1, 0)));
        gameplayState->moveRightPressed();
        REQUIRE(gameplayState->checkCursorPos(Utility::Point(1, 0)));
    }

    SECTION("Testing cursor upward movement")
    {
        gameplayState->setPosition(Utility::Point(0, 1));
        REQUIRE(gameplayState->checkCursorPos(Utility::Point(0, 1)));
        gameplayState->moveUpPressed();
        REQUIRE(gameplayState->checkCursorPos(Utility::Point(0, 0)));
    }

    SECTION("Testing cursor upward movement into a wall")
    {
        REQUIRE(gameplayState->checkCursorPos(Utility::Point(0, 0)));
        gameplayState->moveUpPressed();
        REQUIRE(gameplayState->checkCursorPos(Utility::Point(0, 0)));
    }
}


}