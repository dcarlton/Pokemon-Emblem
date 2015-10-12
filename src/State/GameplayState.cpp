#include "GameplayState.h"

GameplayState::GameplayState()
{
    initGenericMap();
    allPokemon.push_back(Gameplay::Pokemon());
}

void GameplayState::initGenericMap()
{
    std::vector<Gameplay::Terrain> column;
    int size = 10;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            column.push_back(Gameplay::Terrain());
        }
        map.push_back(column);
    }
}

void GameplayState::draw()
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

void GameplayState::moveDownPressed()
{
    if (cursorPos.y < 9)
        (cursorPos.y)++;
}

void GameplayState::moveLeftPressed()
{
    if (cursorPos.x > 0)
        (cursorPos.x)--;
}

void GameplayState::moveRightPressed()
{
    if (cursorPos.x < 9)
        (cursorPos.x)++;
}

void GameplayState::moveUpPressed()
{
    if (cursorPos.y > 0)
        (cursorPos.y)--;
}

void GameplayState::update()
{
}