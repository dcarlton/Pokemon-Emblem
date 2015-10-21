#include "catch.hpp"

#include "../src/State/State.h"
#include "../src/State/StateStack.h"


namespace State
{

class TestState: public State
{
public:
    int id;

    void draw() {};
    void update() {};
};


TEST_CASE("Testing the stack of States")
{
    clearState();
    std::shared_ptr<TestState> state = {std::make_shared<TestState>()};
    std::shared_ptr<TestState> state2 = {std::make_shared<TestState>()};

    SECTION("Add a state to the state stack")
    {
        CHECK_THROWS_AS(getCurrentState(), NoStateException);
        addState(state);
        REQUIRE(getCurrentState() == state);
    }

    SECTION("Exit a state")
    {
        addState(state);
        exitState();
        REQUIRE_THROWS_AS(getCurrentState(), NoStateException);
    }

    SECTION("Exit a state when no state exists")
    {
        REQUIRE_THROWS_AS(exitState(), NoStateException);
    }

    SECTION("Replace a state")
    {
        state->id = 1;
        addState(state);

        state2->id = 2;
        replaceState(state2);

        CHECK((dynamic_cast<TestState&> (*(getCurrentState()))).id == 2);

        exitState();
        REQUIRE_THROWS_AS(getCurrentState(), NoStateException);
    }

    SECTION("Replace a state when no state exists")
    {
        REQUIRE_THROWS_AS(replaceState(state), NoStateException);
    }

    SECTION("Reset the stack")
    {
        addState(state);
        addState(state2);

        std::shared_ptr<TestState> state3 = {std::make_shared<TestState>()};
        state3->id = 3;
        resetState(state3);
        CHECK((dynamic_cast<TestState&> (*(getCurrentState()))).id == 3);

        exitState();
        REQUIRE_THROWS_AS(getCurrentState(), NoStateException);
    }

    SECTION("Reset the empty stack")
    {
        state->id = 1;
        resetState(state);

        CHECK((dynamic_cast<TestState&> (*(getCurrentState()))).id == 1);
        exitState();
        REQUIRE_THROWS_AS(getCurrentState(), NoStateException);
    }

    SECTION("Clear the stack")
    {
        addState(state);
        clearState();
        REQUIRE_THROWS_AS(getCurrentState(), NoStateException);
    }

    SECTION("Clear the empty stack")
    {
        REQUIRE_NOTHROW(clearState());
    }
}

}