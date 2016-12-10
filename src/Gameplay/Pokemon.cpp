#include "../Filesystem/Pokedex.h"
#include "Pokemon.h"


Gameplay::Pokemon::Pokemon(std::string pokemonName, unsigned int level, AllianceEnum startingAlliance)
{
    alliance = startingAlliance;
    name = pokemonName;
    num = Filesystem::Pokedex::getNum(name);

    level = validateLevel(level);
    stats = Gameplay::PokemonStats(name, level);

    moves[0] = std::make_shared<Gameplay::Move>();
    moves[1] = nullptr;
    moves[2] = nullptr;
    moves[3] = nullptr;
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
