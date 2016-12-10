#include "ChoosingAttackTargetState.h"
#include "../Audio/DJ.h"
#include "EnemyTurnState.h"
#include "../Gameplay/Pokemon.h"
#include "Controller/PokemonUtils.h"
#include "StateStack.h"

#include "SimpleIni.h"
CSimpleIniA ini;

// Default constructor, shouldn't be called.
State::ChoosingAttackTargetState::ChoosingAttackTargetState()
{

}

// Constructor to initialize everything.
State::ChoosingAttackTargetState::ChoosingAttackTargetState(State* prevState, std::shared_ptr<Gameplay::World> world)
{
    _originalPos = world->getCursorPos();
    _prevState = prevState;
    _world = world;
}

// Called when the back button is pressed. We return the cursor
// to its original position and go back to choosing what action
// to do.
void State::ChoosingAttackTargetState::backButtonPressed()
{
    _world->setCursorPos(_originalPos);
    exitState();
}

// Draw the map.
void State::ChoosingAttackTargetState::draw()
{
    _prevState->draw();
}

// Called when the down button is pressed to move the cursor down.
void State::ChoosingAttackTargetState::moveDownPressed()
{
    _world->moveCursorDownIfInRange(_originalPos, 1);
}

// Called when the left button is pressed to move the cursor left.
void State::ChoosingAttackTargetState::moveLeftPressed()
{
    _world->moveCursorLeftIfInRange(_originalPos, 1);
}

// Called when the right button is pressed to move the cursor right.
void State::ChoosingAttackTargetState::moveRightPressed()
{
    _world->moveCursorRightIfInRange(_originalPos, 1);
}

// Called when the up button is pressed to move the cursor up.
void State::ChoosingAttackTargetState::moveUpPressed()
{
    _world->moveCursorUpIfInRange(_originalPos, 1);
}

// Called when the select button is pressed to attack the Pokemon the
// cursor is over.
void State::ChoosingAttackTargetState::selectButtonPressed()
{
    // TODO: Pull this out into a method somewhere in Gameplay
    std::shared_ptr<Gameplay::Pokemon> attackingPokemon = _world->getPokemonFromPosition(_originalPos);
    std::shared_ptr<Gameplay::Pokemon> targetPokemon = _world->getPokemonUnderCursor();

    if (targetPokemon != nullptr && targetPokemon->alliance != attackingPokemon->alliance)
    {
        // TODO: Deal with obvious repeated code.
        targetPokemon->stats.takeDamage(attackingPokemon->stats.getAttack() + 10 - targetPokemon->stats.getDefense());
        if (targetPokemon->stats.getCurrentHP() <= 0)
        {
            _world->pokemonFainted(_world->getCursorPos());
        }
        else
        {
            attackingPokemon->stats.takeDamage(targetPokemon->stats.getAttack() + 10 - targetPokemon->stats.getDefense());
            if (targetPokemon->stats.getCurrentHP() <= 0)
            {
                _world->pokemonFainted(_world->getCursorPos());
            }
        }

        Audio::playSoundEffect(Audio::SoundEffect::TestSoundEffect);
        Controller::endPokemonsTurn(attackingPokemon, _world);
    }
}

// Called every frame.
void State::ChoosingAttackTargetState::update()
{

}