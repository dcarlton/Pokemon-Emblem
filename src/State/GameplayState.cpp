#include "GameplayState.h"
#include "Controller/MoveUtils.h"
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
        _map.push_back(column);
    }

    std::shared_ptr<Gameplay::Pokemon> pokemon = {std::make_shared<Gameplay::Pokemon> ()};
    _map[0][0].pokemon = pokemon;
}

void State::GameplayState::draw()
{
    for (unsigned int x = 0; x < _map.size(); x++)
    {
        for (unsigned int y = 0; y < _map[x].size(); y++)
        {
            _map[x][y].draw(Utility::Point(x * 24, y * 24));
        }
    }

    /*for (std::shared_ptr<Gameplay::Pokemon> pokemon: allPokemon)
    {
        GUI::drawImage(pokemon->image, Utility::Point(pokemon->position.x * 24, pokemon->position.y * 24));
    }*/

    GUI::drawImage(_cursorImage, Utility::Point(_cursorPos.x * 24, _cursorPos.y * 24));
}

void State::GameplayState::moveDownPressed()
{
    _cursorPos.y = ::State::Controller::moveDown(_cursorPos.y, _map[0].size() - 1);
}

void State::GameplayState::moveLeftPressed()
{
    _cursorPos.x = ::State::Controller::moveLeft(_cursorPos.x, 0);
}

void State::GameplayState::moveRightPressed()
{
    _cursorPos.x = ::State::Controller::moveRight(_cursorPos.x, _map[0].size() - 1);
}

void State::GameplayState::moveUpPressed()
{
    _cursorPos.y = ::State::Controller::moveUp(_cursorPos.y, 0);
}

void State::GameplayState::selectButtonPressed()
{
    addState({std::make_shared<PokemonSelectedState> (this, _map, _cursorPos)});
}

void State::GameplayState::update()
{
}