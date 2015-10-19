#ifndef STATESTACK_H
#define STATESTACK_H

#include <exception>
#include <memory>
#include <vector>


namespace State
{

class State;


class NoStateException: public std::exception{};

class StateStack
{
public:
    std::shared_ptr<State> currentState = nullptr;

    void addState(std::shared_ptr<State> state);
    void exitState();
    void replaceState(std::shared_ptr<State> state);
    void resetState(std::shared_ptr<State> state);

private:
    std::vector<std::shared_ptr<State>> stack;
};

}

#endif