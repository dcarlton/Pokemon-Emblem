#include <time.h>

#include "Battle.h"
#include "../Utility/Point.h"
#include "Terrain.h"


namespace
{
    // One Pokemon attacks another. Doesn't handle counter attacks or double attacks.
    // Returns true if the Pokemon is knocked out.
    bool attack(std::shared_ptr<Gameplay::World> world, Utility::Point attackerPosition, Gameplay::Move move, Utility::Point targetPosition)
    {
        std::shared_ptr<Gameplay::Pokemon> attackingPokemon = world->getPokemonFromPosition(attackerPosition);
        std::shared_ptr<Gameplay::Pokemon> targetPokemon = world->getPokemonFromPosition(targetPosition);

        if (attackerPosition.distanceFrom(targetPosition) <= move.getRange())
        {
            Gameplay::Terrain targetTerrain = world->getTerrainFromPosition(targetPosition);
            int accuracy = (int)move.getAccuracy() + (int)attackingPokemon->stats.getAccuracy();
            int evasion = (int)targetPokemon->stats.getEvasion() + targetTerrain.getAvoid();

            if (move.alwaysHits() || (rand() % 100) < (accuracy - evasion))
            {
                int attack = attackingPokemon->stats.getAttack();
                int defense = targetPokemon->stats.getDefense() + targetTerrain.getDefense();
                int damage = move.calculateDamage(attack, defense);  // Note that damage can be negative if the move heals its target.
                targetPokemon->stats.takeDamage(damage);
                
                move.runSideEffects(attackingPokemon, targetPokemon);

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

        return false;
    }
}

// Enact a fight where one Pokemon attacks another, accounting for double
// attacks and range. If either Pokemon runs out of health, it should faint.
void Gameplay::fight(std::shared_ptr<Gameplay::World> world, Utility::Point attackerPosition, Gameplay::Move move, Utility::Point targetPosition)
{
    bool pokemonFainted = attack(world, attackerPosition, move, targetPosition);
    if (!pokemonFainted)
    {
        // Counterattack!
        attack(world, targetPosition, *(world->getPokemonFromPosition(targetPosition)->moves[0]), attackerPosition);
    }
}