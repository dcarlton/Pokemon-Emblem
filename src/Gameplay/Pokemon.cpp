#include <algorithm>

#include "../Filesystem/Pokedex.h"
#include "Pokemon.h"


Gameplay::Pokemon::Pokemon(std::string pokemonName, unsigned int level, AllianceEnum startingAlliance)
{
    alliance = startingAlliance;
    name = pokemonName;
    num = Filesystem::Pokedex::getNum(name);

    level = validateLevel(level);
    moves = Filesystem::Pokedex::getMoves(pokemonName, level);
    stats = Gameplay::PokemonStats(name, level);
}

// Returns the range of the longest ranged move this Pokemon knows that
// hits the target alliance.
int Gameplay::Pokemon::getMaxRange(Gameplay::AllianceEnum targetAlliance)
{
    int allianceBitwiseFlag = alliance == targetAlliance ? Gameplay::TARGET::ALLY : Gameplay::TARGET::ENEMY;
    int maxRange = -1;

	for (unsigned int i = 0; i < getNumMoves(); i++)
	{
        if (moves[i]->getTarget() & allianceBitwiseFlag)
        {
            maxRange = std::max(maxRange, (int)moves[i]->getRange());
        }
	}

    return maxRange;
}

// Get the number of moves this Pokemon knows. I'm assuming that
// its move list has no gaps, so if the third slot has a move, then
// the first and second move slots also have a move.
unsigned int Gameplay::Pokemon::getNumMoves()
{
    for (int i = 3; i >= 0; i--)
    {
        if (moves[i] != nullptr)
        {
            return i + 1;
        }
    }

    return 0;
}

// Returns the alliance that this Pokemon is not on.
Gameplay::AllianceEnum Gameplay::Pokemon::getOpposingAlliance()
{
    return (Gameplay::AllianceEnum)((~alliance) & 1);  // Turns 0 to 1 and vice versa.
}

// Call at the start of the Pokemon's turn to set hasMoved and
// handle the stat boosts disappearing over time.
void Gameplay::Pokemon::onStartTurn()
{
    hasMoved = false;
    stats.onStartTurn();
}

// Guarantee that the Pokemon's level is a valid level.
unsigned int Gameplay::Pokemon::validateLevel(unsigned int level)
{
    if (level == 0)
    {
        return 1;
    }
    else if (level > 100)
    {
        return 100;
    }
    else
    {
        return level;
    }
}
