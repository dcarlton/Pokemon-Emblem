#include "Pokemon.h"

Gameplay::Pokemon::Pokemon(PokemonSpecies species, unsigned int level, AllianceEnum startingAlliance)
{
    alliance = startingAlliance;
    this->species = species;

    level = validateLevel(level);
    stats.level = level;
    //stats = Formulas::getStats(species, level);
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
