#include "State.h"
#include "StateStack.h"


void State::StateStack::addState(std::shared_ptr<State> state)
{
    stack.push_back(state);
    currentState = state;
}

void State::StateStack::exitState()
{
    if (stack.empty())
        throw NoStateException();

    stack.pop_back();

    if (stack.empty())
        currentState = nullptr;
    else
        currentState = stack.back();
}

void State::StateStack::replaceState(std::shared_ptr<State> state)
{
    exitState();
    addState(state);
}

void State::StateStack::resetState(std::shared_ptr<State> state)
{
    while (!stack.empty())
        exitState();

    addState(state);
}