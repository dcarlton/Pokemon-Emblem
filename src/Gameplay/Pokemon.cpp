#include "Pokemon.h"

Gameplay::Pokemon::Pokemon(PokemonSpecies species, AllianceEnum startingAlliance)
{
    alliance = startingAlliance;
    this->species = species;
}
