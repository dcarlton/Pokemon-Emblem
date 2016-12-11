#include "../Filesystem/Pokedex.h"
#include "Pokemon.h"


Gameplay::Pokemon::Pokemon(std::string pokemonName, unsigned int level, AllianceEnum startingAlliance)
{
    alliance = startingAlliance;
    name = pokemonName;
    num = Filesystem::Pokedex::getNum(name);

    level = validateLevel(level);
    stats = Gameplay::PokemonStats(name, level);

    moves[0] = std::make_shared<Gameplay::Move>("A");
    moves[1] = std::make_shared<Gameplay::Move>("B");
    moves[2] = std::make_shared<Gameplay::Move>("C");
    moves[3] = std::make_shared<Gameplay::Move>();
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
