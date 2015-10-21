#include "GameplayState.h"
#include "PokemonSelectedState.h"
#include "StateStack.h"


State::GameplayState::GameplayState()
{
    initGenericMap();
}

void State::GameplayState::initGenericMap()
{
    std::vector<Gameplay::Tile> column;
    const int size = 10;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {

            column.push_back(Gameplay::Tile());
        }
        map.push_back(column);
    }

    std::shared_ptr<Gameplay::Pokemon> pokemon = {std::make_shared<Gameplay::Pokemon> ()};
    map[0][0].pokemon = pokemon;
    allPokemon.push_back(pokemon);

}

void State::GameplayState::draw()
{
    for (unsigned int x = 0; x < map.size(); x++)
    {
        for (unsigned int y = 0; y < map[x].size(); y++)
        {
            map[x][y].draw(Utility::Point(x * 24, y * 24));
        }
    }

    /*for (std::shared_ptr<Gameplay::Pokemon> pokemon: allPokemon)
    {
        GUI::drawImage(pokemon->image, Utility::Point(pokemon->position.x * 24, pokemon->position.y * 24));
    }*/

    GUI::drawImage(cursorImage, Utility::Point(cursorPos.x * 24, cursorPos.y * 24));
}

void State::GameplayState::moveDownPressed()
{
    if (cursorPos.y < map.size() - 1)
        (cursorPos.y)++;
}

void State::GameplayState::moveLeftPressed()
{
    if (cursorPos.x > 0)
        (cursorPos.x)--;
}

void State::GameplayState::moveRightPressed()
{
    if (cursorPos.x < map.size() - 1)
        (cursorPos.x)++;
}

void State::GameplayState::moveUpPressed()
{
    if (cursorPos.y > 0)
        (cursorPos.y)--;
}

void State::GameplayState::selectButtonPressed()
{
    addState({std::make_shared<PokemonSelectedState> (this, map, cursorPos)});
}

void State::GameplayState::update()
{
}