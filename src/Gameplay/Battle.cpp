#include "Battle.h"
#include "../Utility/Point.h"


namespace
{
    // One Pokemon attacks another. Doesn't handle counter attacks or double attacks.
    // Returns true if the Pokemon is knocked out.
    bool attack(std::shared_ptr<Gameplay::World> world, Utility::Point attackerPosition, Utility::Point targetPosition)
    {
        std::shared_ptr<Gameplay::Pokemon> attackingPokemon = world->getPokemonFromPosition(attackerPosition);
        std::shared_ptr<Gameplay::Pokemon> targetPokemon = world->getPokemonFromPosition(targetPosition);

        targetPokemon->stats.takeDamage((attackingPokemon->stats.getAttack() + attackingPokemon->moves[0]->getBasePower()) - targetPokemon->stats.getDefense());
        if (targetPokemon->stats.getCurrentHP() <= 0)
        {
            world->pokemonFainted(targetPosition);
            return true;
        }
        else
        {
            return false;
        }
    }
}

// Enact a fight where one Pokemon attacks another, accounting for double
// attacks and range. If either Pokemon runs out of health, it should faint.
void Gameplay::fight(std::shared_ptr<Gameplay::World> world, Utility::Point attackerPosition, Utility::Point targetPosition)
{
    bool pokemonFainted = attack(world, attackerPosition, targetPosition);
    if (!pokemonFainted)
    {
        // Counterattack!
        attack(world, targetPosition, attackerPosition);
    }
}