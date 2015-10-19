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
    StateStack stateStack;
    std::shared_ptr<TestState> state = {std::make_shared<TestState>()};
    std::shared_ptr<TestState> state2 = {std::make_shared<TestState>()};

    SECTION("Add a state to the state stack")
    {
        CHECK(stateStack.currentState == nullptr);
        stateStack.addState(state);
        REQUIRE(stateStack.currentState == state);
    }

    SECTION("Exit a state")
    {
        stateStack.addState(state);
        stateStack.exitState();
        REQUIRE(stateStack.currentState == nullptr);
    }

    SECTION("Exit a state when no state exists")
    {
        REQUIRE_THROWS_AS(stateStack.exitState(), NoStateException);
    }

    SECTION("Replace a state")
    {
        state->id = 1;
        stateStack.addState(state);

        state2->id = 2;
        stateStack.replaceState(state2);

        CHECK((dynamic_cast<TestState&> (*(stateStack.currentState))).id == 2);

        stateStack.exitState();
        REQUIRE(stateStack.currentState == nullptr);
    }

    SECTION("Replace a state when no state exists")
    {
        REQUIRE_THROWS_AS(stateStack.replaceState(state), NoStateException);
    }

    SECTION("Reset the stack")
    {
        stateStack.addState(state);
        stateStack.addState(state2);

        std::shared_ptr<TestState> state3 = {std::make_shared<TestState>()};
        state3->id = 3;
        stateStack.resetState(state3);
        CHECK((dynamic_cast<TestState&> (*(stateStack.currentState))).id == 3);

        stateStack.exitState();
        REQUIRE(stateStack.currentState == nullptr);
    }

    SECTION("Reset the empty stack")
    {
        state->id = 1;
        stateStack.resetState(state);

        CHECK((dynamic_cast<TestState&> (*(stateStack.currentState))).id == 1);
        stateStack.exitState();
        REQUIRE(stateStack.currentState == nullptr);
    }
}

}