#include "AllianceEnum.h"
#include "../State/Controller/MoveUtils.h"
#include "Pokemon.h"
#include "PokemonEnum.h"
#include "World.h"


// Default constructor.
Gameplay::World::World()
{
    _cursorPos = Utility::Point(0, 0);

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

    std::shared_ptr<Gameplay::Pokemon> pokemon = {std::make_shared<Gameplay::Pokemon> (Gameplay::PokemonSpecies::BULBASAUR, 3, Gameplay::AllianceEnum::Player)};
    addPokemon(pokemon, Utility::Point(0, 0));

    pokemon = {std::make_shared<Gameplay::Pokemon> (Gameplay::PokemonSpecies::CHARMANDER, 3, Gameplay::AllianceEnum::Enemy)};
    addPokemon(pokemon, Utility::Point(0, 1));

    pokemon = {std::make_shared<Gameplay::Pokemon> (Gameplay::PokemonSpecies::BULBASAUR, 2, Gameplay::AllianceEnum::Player)};
    addPokemon(pokemon, Utility::Point(1, 0));
}

// Add a Pokemon to the world. We need this function to keep
// track of every Pokemon on each team, to tell when all Pokemon on a
// team have finished moving.
void Gameplay::World::addPokemon(std::shared_ptr<Gameplay::Pokemon> pokemon, Utility::Point position)
{
    if (position.x >= _map.size() || position.y >= _map[0].size() || _map[position.x][position.y].pokemon != NULL)
        return;

    _map[position.x][position.y].pokemon = pokemon;
    switch (pokemon->alliance)
    {
        case AllianceEnum::Enemy:
            _enemyPokemon.push_back(pokemon);
            break;

        case AllianceEnum::Player:
            _playerPokemon.push_back(pokemon);
            break;
    }
}

// Draw the current world.
void Gameplay::World::drawWorld()
{
    for (unsigned int x = 0; x < _map.size(); x++)
    {
        for (unsigned int y = 0; y < _map[x].size(); y++)
        {
            _map[x][y].draw(Utility::Point(x, y));
        }
    }

    /*for (std::shared_ptr<Gameplay::Pokemon> pokemon: allPokemon)
    {
        GUI::drawImage(pokemon->image, Utility::Point(pokemon->position.x * 24, pokemon->position.y * 24));
    }*/

    GUI::drawImage(_cursorImage, _cursorPos);
    GUI::drawPokemonStats(getPokemonUnderCursor());
}

// Return the current position of the cursor.
Utility::Point Gameplay::World::getCursorPos()
{
    return _cursorPos;
}

std::vector<Utility::Point> Gameplay::World::getEnemyPokemonPositions()
{
    std::vector<Utility::Point> points;
    for (uint32 x = 0; x < _map.size(); x++)
    {
        for (uint32 y = 0; y < _map[0].size(); y++)
        {
            if (_map[x][y].pokemon != nullptr && _map[x][y].pokemon->alliance == AllianceEnum::Enemy)
            {
                points.push_back(Utility::Point(x, y));
            }
        }
    }

    return points;
}

// Return all points within a certain distance from the originating point.
std::vector<Utility::Point> Gameplay::World::getPointsInRange(Utility::Point startingPosition, uint32 range)
{
    auto pointsWithinDistance = startingPosition.getPointsWithinDistance(range);
    for (int i = pointsWithinDistance.size() - 1; i >= 0; i--)
    {
        Utility::Point position = pointsWithinDistance[i];
        if (position.x < 0 || position.x >= _map.size() || position.y < 0 || position.y >= _map[0].size() || position == startingPosition)
        {
            pointsWithinDistance.erase(pointsWithinDistance.begin() + i);
        }
    }

    return pointsWithinDistance;
}

// Return a pointer to the Pokemon at the specified position.
std::shared_ptr<Gameplay::Pokemon> Gameplay::World::getPokemonFromPosition(Utility::Point position)
{
    if (position.x >= _map.size() && position.y >= _map[0].size())
        return NULL;

    return _map[position.x][position.y].pokemon;
}

// Return a pointer to the Pokemon under the map cursor.
std::shared_ptr<Gameplay::Pokemon> Gameplay::World::getPokemonUnderCursor()
{
    return _map[_cursorPos.x][_cursorPos.y].pokemon;
}

// Returns true if all Pokemon with the Player alliance have moved this turn.
bool Gameplay::World::hasAllPlayerPokemonMoved()
{
    for (unsigned int i = 0; i < _playerPokemon.size(); i++)
    {
        if (!_playerPokemon[i]->hasMoved)
            return false;
    }

    return true;
}

// Move the map cursor down, if possible.
void Gameplay::World::moveCursorDown()
{
    _cursorPos.y = State::Controller::moveDown(_cursorPos.y, _map[0].size() - 1);
}

// Move the cursor down, only if it stays in the map and doesn't go
// out of range from a starting position.
void Gameplay::World::moveCursorDownIfInRange(Utility::Point startingPosition, unsigned int maxRange)
{
    if (_cursorPos.y >= (_map[0].size() - 1))
        return;

    Utility::Point newPosition = _cursorPos;
    newPosition.y++;
    if (newPosition.distanceFrom(startingPosition) <= maxRange)
        _cursorPos = newPosition;
}

// Move the cursor left, if it doesn't go outside the map.
void Gameplay::World::moveCursorLeft()
{
    _cursorPos.x = State::Controller::moveLeft(_cursorPos.x, 0);
}

// Move the cursor left, only if it stays in the map and doesn't go
// out of range from a starting position.
void Gameplay::World::moveCursorLeftIfInRange(Utility::Point startingPosition, unsigned int maxRange)
{
    if (_cursorPos.x <= 0)
        return;

    Utility::Point newPosition = _cursorPos;
    newPosition.x--;
    if (newPosition.distanceFrom(startingPosition) <= maxRange)
        _cursorPos = newPosition;
}

// Move the cursor to the right, if it doesn't go outside the map.
void Gameplay::World::moveCursorRight()
{
    _cursorPos.x = State::Controller::moveRight(_cursorPos.x, _map[0].size() - 1);
}

// Move the cursor right, only if it stays in the map and doesn't go
// out of range from a starting position.
void Gameplay::World::moveCursorRightIfInRange(Utility::Point startingPosition, unsigned int maxRange)
{
    if (_cursorPos.x >= _map.size() - 1)
        return;

    Utility::Point newPosition = _cursorPos;
    newPosition.x++;
    if (newPosition.distanceFrom(startingPosition) <= maxRange)
        _cursorPos = newPosition;
}

// Move the cursor up, if it doesn't go outside the map.
void Gameplay::World::moveCursorUp()
{
    _cursorPos.y = State::Controller::moveUp(_cursorPos.y, 0);
}

// Move the cursor up, only if it stays in the map and doesn't go
// out of range from a starting position.
void Gameplay::World::moveCursorUpIfInRange(Utility::Point startingPosition, unsigned int maxRange)
{
    if (_cursorPos.y <= 0)
        return;

    Utility::Point newPosition = _cursorPos;
    newPosition.y--;
    if (newPosition.distanceFrom(startingPosition) <= maxRange)
        _cursorPos = newPosition;
}

// Move a Pokemon from one position to another.
bool Gameplay::World::movePokemon(Utility::Point oldPosition, Utility::Point newPosition)
{
    if (oldPosition.x >= _map.size() && oldPosition.y >= _map[0].size())
        return false;

    if (newPosition.x >= _map.size() && newPosition.y >= _map[0].size())
        return false;

    if (_map[oldPosition.x][oldPosition.y].pokemon == NULL || _map[newPosition.x][newPosition.y].pokemon != NULL)
        return false;

    _map[newPosition.x][newPosition.y].pokemon = _map[oldPosition.x][oldPosition.y].pokemon;
    _map[oldPosition.x][oldPosition.y].pokemon = nullptr;

    return true;
}

// Call when a Pokemon has run out of HP to remove it from the world.
void Gameplay::World::pokemonFainted(Utility::Point faintedPokemonPosition)
{
    std::shared_ptr<Gameplay::Pokemon> faintedPokemon = getPokemonFromPosition(faintedPokemonPosition);
    if (faintedPokemon != nullptr && faintedPokemon->stats.getCurrentHP() <= 0)
    {
        _map[faintedPokemonPosition.x][faintedPokemonPosition.y].pokemon = nullptr;
        switch (faintedPokemon->alliance)
        {
            case AllianceEnum::Enemy:
                removePokemonFromList(faintedPokemon, _enemyPokemon);
                break;

            case AllianceEnum::Player:
                removePokemonFromList(faintedPokemon, _playerPokemon);
                break;
        }
    }
}

// Remove a Pokemon from a vector of Pokemon.
void Gameplay::World::removePokemonFromList(std::shared_ptr<Gameplay::Pokemon> pokemon, std::vector<std::shared_ptr<Gameplay::Pokemon>> pokemonList)
{
    for (std::vector<std::shared_ptr<Gameplay::Pokemon>>::iterator iter = pokemonList.begin(); iter != pokemonList.end(); iter++)
    {
        if (*iter == pokemon)
        {
            pokemonList.erase(iter);
            return;
        }
    }
}


// Set all of the enemy Pokemon's hasMoved property to false.
void Gameplay::World::resetWhetherEnemyPokemonHaveMoved()
{
    resetWhetherPokemonHaveMoved(_enemyPokemon);
}

// Set all of the player Pokemon's hasMoved property to false.
void Gameplay::World::resetWhetherPlayerPokemonHaveMoved()
{
    resetWhetherPokemonHaveMoved(_playerPokemon);
}

// Set the hasMoved property to false for every Pokemon passed in.
void Gameplay::World::resetWhetherPokemonHaveMoved(std::vector<std::shared_ptr<Gameplay::Pokemon>> pokemans)
{
    for (unsigned int i = 0; i < pokemans.size(); i++)
    {
        pokemans[i]->hasMoved = false;
    }
}

// Set the current position of the map cursor.
bool Gameplay::World::setCursorPos(Utility::Point newPosition)
{
    _cursorPos = newPosition;
    return true;
}