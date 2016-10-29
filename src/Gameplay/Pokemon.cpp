#include "Pokemon.h"

Gameplay::Pokemon::Pokemon(PokemonSpecies species, AllianceEnum startingAlliance)
{
    alliance = startingAlliance;
    this->species = species;

    switch (alliance)
    {
        case AllianceEnum::Enemy:
            image = GUI::getImage(GUI::ImageEnum::TestPokemonEnemy);
            break;

        case AllianceEnum::Player:
            image = GUI::getImage(GUI::ImageEnum::TestPokemonAlly);
            break;
    }
}
