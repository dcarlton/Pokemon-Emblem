#include "GameplayState.h"


GameplayState::GameplayState()
{
    initGenericMap();
    allPokemon.push_back(Pokemon());
}

void GameplayState::initGenericMap()
{
    std::vector<Terrain> column;
    int size = 10;
    Terrain terrain;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            terrain.image = GUI::getImage(Image::testTile);
            column.push_back(terrain);
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
            GUI::drawImage(map[x][y].image, x * 24, y * 24, 24, 24);
        }
    }

    for (Pokemon pokemon: allPokemon)
    {
        GUI::drawImage(pokemon.image, pokemon.position.x * 24, pokemon.position.y * 24, 24, 24);
    }

    GUI::drawImage(cursorImage, cursorPos.x * 24, cursorPos.y * 24, 24, 24);
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