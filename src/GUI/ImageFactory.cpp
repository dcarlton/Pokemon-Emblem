#include <exception>

#include "../Utility/Color.h"
#include "ImageFactory.h"


namespace
{
    const Utility::Color blackColorKey(0, 0, 0);
    const Utility::Color whiteColorKey(0xFF, 0xFF, 0xFF);

    // First image defined in this file will crash.
    // Second image defined in this file will be transparent.
    // I have no freaking clue why.
    const GUI::Image BROKEN_IMAGE = GUI::Image("resources/Pokemon/TestPokemon.bmp", whiteColorKey, Utility::Point(24, 24));
    const GUI::Image TRANSPARENT_IMAGE = GUI::Image("resources/Pokemon/TestPokemon.bmp", whiteColorKey, Utility::Point(24, 24));

    const GUI::Image GAMEPLAY_CURSOR = GUI::Image("resources/GameplayCursor.bmp", whiteColorKey, Utility::Point(24, 24));
    const GUI::Image MENU_ITEM = GUI::Image("resources/MenuItem.bmp", whiteColorKey, Utility::Point(64, 16));
    const GUI::Image POKEMON_SPRITE_SHEET = GUI::Image("resources/Pokemon/SpriteSheet.bmp", whiteColorKey, Utility::Point(1152, 648));
    const GUI::Image TEST_POKEMON = GUI::Image("resources/Pokemon/TestPokemon.bmp", whiteColorKey, Utility::Point(24, 24));
    const GUI::Image TEST_POKEMON_ALLY = GUI::Image("resources/Pokemon/TestPokemonAlly.bmp", whiteColorKey, Utility::Point(24, 24));
    const GUI::Image TEST_POKEMON_ENEMY = GUI::Image("resources/Pokemon/TestPokemonEnemy.bmp", whiteColorKey, Utility::Point(24, 24));
    const GUI::Image TEST_TILE = GUI::Image("resources/Tiles/TestTile.bmp", blackColorKey, Utility::Point(24, 24));
}

const GUI::Image* GUI::makeImage(GUI::ImageEnum imageEnum)
{
    switch (imageEnum)
    {
        case GUI::ImageEnum::GameplayCursor:
            return &GAMEPLAY_CURSOR;

        case GUI::ImageEnum::MenuItem:
            return &MENU_ITEM;

        case GUI::ImageEnum::PokemonSpriteSheet:
            return &POKEMON_SPRITE_SHEET;

        case GUI::ImageEnum::TestPokemon:
            return &TEST_POKEMON;

        case GUI::ImageEnum::TestPokemonAlly:
            return &TEST_POKEMON_ALLY;

        case GUI::ImageEnum::TestPokemonEnemy:
            return &TEST_POKEMON_ENEMY;

        case GUI::ImageEnum::TestTile:
            return &TEST_TILE;

        default:
            return NULL;
    }
}