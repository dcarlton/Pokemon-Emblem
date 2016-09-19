#include <exception>

#include "../Utility/Color.h"
#include "ImageFactory.h"


namespace
{
    const Utility::Color blackColorKey(0, 0, 0);
    const Utility::Color whiteColorKey(0xFF, 0xFF, 0xFF);
}

GUI::Image GUI::makeImage(GUI::ImageEnum imageEnum)
{
    switch (imageEnum)
    {
        case GUI::ImageEnum::GameplayCursor:
            return Image("..\\resources\\GameplayCursor.bmp", whiteColorKey, Utility::Size(24, 24));
            break;

        case GUI::ImageEnum::MenuItem:
            return Image("..\\resources\\MenuItem.bmp", whiteColorKey, Utility::Size(64, 16));

        case GUI::ImageEnum::TestPokemon:
            return Image("..\\resources\\Pokemon\\TestPokemon.bmp", whiteColorKey, Utility::Size(24, 24));
            break;

        case GUI::ImageEnum::TestPokemonAlly:
            return Image("..\\resources\\Pokemon\\TestPokemonAlly.bmp", whiteColorKey, Utility::Size(24, 24));
            break;

        case GUI::ImageEnum::TestPokemonEnemy:
            return Image("..\\resources\\Pokemon\\TestPokemonEnemy.bmp", whiteColorKey, Utility::Size(24, 24));
            break;

        case GUI::ImageEnum::TestTile:
            return Image("..\\resources\\Tiles\\TestTile.bmp", blackColorKey, Utility::Size(24, 24));
            break;

        default:
            return Image();
            break;
    }
}