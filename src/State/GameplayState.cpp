#include "GameplayState.h"

State::GameplayState::GameplayState()
{
    initGenericMap();
    allPokemon.push_back(Gameplay::Pokemon());
}

void State::GameplayState::initGenericMap()
{
    std::vector<Gameplay::Terrain> column;
    const int size = 10;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            column.push_back(Gameplay::Terrain());
        }
        map.push_back(column);
    }
}

void State::GameplayState::draw()
{
    for (unsigned int x = 0; x < map.size(); x++)
    {
        for (unsigned int y = 0; y < map[x].size(); y++)
        {
            GUI::drawImage(map[x][y].image, Point(x * 24, y * 24));
        }
    }

    for (Gameplay::Pokemon pokemon: allPokemon)
    {
        GUI::drawImage(pokemon.image, Point(pokemon.position.x * 24, pokemon.position.y * 24));
    }

    GUI::drawImage(cursorImage, Point(cursorPos.x * 24, cursorPos.y * 24));
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

void State::GameplayState::update()
{
}