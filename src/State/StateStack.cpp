#include <string>
#include <typeinfo>

#include "../Utility/Log.h"
#include "State.h"
#include "StateStack.h"


namespace
{
    static std::vector<std::shared_ptr<State::State>> stack;
}

void State::addState(std::shared_ptr<State> state)
{
    std::string stateName = std::string(typeid(*state).name());
    Utility::log("Adding state " + stateName);
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

    std::string stateName = std::string(typeid(*(stack.back())).name());
    Utility::log("Exiting state " + stateName);
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

// Reset the current state stack to just the bottom state in the current stack.
void State::resetState()
{
    for (int i = stack.size() - 1; i > 0; i--)
        stack.pop_back();
}

void State::resetState(std::shared_ptr<State> state)
{
    clearState();
    addState(state);
}