#include "Pokemon.h"

Gameplay::Pokemon::Pokemon(AllianceEnum startingAlliance)
{
    alliance = startingAlliance;

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
