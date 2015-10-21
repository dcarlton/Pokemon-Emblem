#ifndef STATESTACK_H
#define STATESTACK_H

#include <exception>
#include <memory>
#include <vector>


// TODO: Add destructor that cleans up the stack
// TODO: Find a reasonably clean and functional way so only states can access
// the utility functions, and only Main can access getCurrentState

// IF YOU ARE NOT A STATE OR THE GAME LOOP, DO NOT INCLUDE THIS FILE
namespace State
{

class State;

class NoStateException: public std::exception{};


void addState(std::shared_ptr<State> state);
void clearState();
void exitState();
std::shared_ptr<State> getCurrentState();
void replaceState(std::shared_ptr<State> state);
void resetState(std::shared_ptr<State> state);

}

#endif