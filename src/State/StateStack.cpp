#include "State.h"
#include "StateStack.h"


namespace
{
    static std::vector<std::shared_ptr<State::State>> stack;
}

void State::addState(std::shared_ptr<State> state)
{
    stack.push_back(state);
}

void State::clearState()
{
    while (!stack.empty())
        exitState();
}

void State::exitState()
{
    if (stack.empty())
        throw NoStateException();

    stack.pop_back();
}

std::shared_ptr<State::State> State::getCurrentState()
{
    if (stack.empty())
        throw NoStateException();

    return stack.back();
}

void State::replaceState(std::shared_ptr<State> state)
{
    exitState();
    addState(state);
}

void State::resetState(std::shared_ptr<State> state)
{
    clearState();
    addState(state);
}