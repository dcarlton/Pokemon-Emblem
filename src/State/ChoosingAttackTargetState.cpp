#include "ChoosingAttackTargetState.h"
#include "EnemyTurnState.h"
#include "../Gameplay/Pokemon.h"
#include "Controller/PokemonUtils.h"
#include "StateStack.h"


// Default constructor, shouldn't be called.
State::ChoosingAttackTargetState::ChoosingAttackTargetState()
{

}

State::ChoosingAttackTargetState::ChoosingAttackTargetState(State* prevState, std::shared_ptr<Gameplay::World> world)
{
    _originalPos = world->getCursorPos();
    _prevState = prevState;
    _world = world;
}

void State::ChoosingAttackTargetState::backButtonPressed()
{
    _world->setCursorPos(_originalPos);
    exitState();
}

void State::ChoosingAttackTargetState::draw()
{
    _prevState->draw();
}

void State::ChoosingAttackTargetState::moveDownPressed()
{
    _world->moveCursorDown();
}

void State::ChoosingAttackTargetState::moveLeftPressed()
{
    _world->moveCursorLeft();
}

void State::ChoosingAttackTargetState::moveRightPressed()
{
    _world->moveCursorRight();
}

void State::ChoosingAttackTargetState::moveUpPressed()
{
    _world->moveCursorUp();
}

void State::ChoosingAttackTargetState::selectButtonPressed()
{
    std::shared_ptr<Gameplay::Pokemon> pokemon = _world->getPokemonUnderCursor();
    if (pokemon != nullptr && pokemon->alliance != _world->getPokemonFromPosition(_originalPos)->alliance)
    {
        pokemon->stats.currentHP -= 5;
        if (pokemon->stats.currentHP <= 0)
        {
            _world->pokemonFainted(_world->getCursorPos());
        }

        Controller::endPokemonsTurn(pokemon, _world);
    }
}

void State::ChoosingAttackTargetState::update()
{

}