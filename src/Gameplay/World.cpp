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
    const int size = 12;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            column.push_back(Gameplay::Tile());
        }
        _map.push_back(column);
    }

    std::shared_ptr<Gameplay::Pokemon> pokemon = {std::make_shared<Gameplay::Pokemon> ("bulbasaur", 5, Gameplay::AllianceEnum::Player)};
    addPokemon(pokemon, Utility::Point(0, 0));

    pokemon = {std::make_shared<Gameplay::Pokemon> ("charmander", 5, Gameplay::AllianceEnum::Enemy)};
    addPokemon(pokemon, Utility::Point(0, 1));

    pokemon = {std::make_shared<Gameplay::Pokemon> ("bulbasaur", 5, Gameplay::AllianceEnum::Player)};
    addPokemon(pokemon, Utility::Point(1, 0));
}

Gameplay::World::World(std::vector<std::vector<Gameplay::Tile>> tiles, Utility::Point cursorPos)
{
    _cursorPos = cursorPos;
    _map = tiles;

    // All of the Pokemon need to be added to the PlayerPokemon and
    // EnemyPokemon lists.
    for (unsigned int i = 0; i < _map.size(); i++)
    {
        for (unsigned int j = 0; j < _map[0].size(); j++)
        {
            if (_map[i][j].pokemon)
            {
                addPokemon(_map[i][j].pokemon, Utility::Point(i, j));
            }
        }
    }
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

// Returns the distance from the given position, to the current Pokemon that
// is an enemy of the given alliance.
int Gameplay::World::distanceFromClosestEnemy(Utility::Point position, Gameplay::AllianceEnum alliance)
{
    // TODO: If there's performance issues, it may be right here.
    for (int i = 1; i <= 60; i++)
    {
        std::vector<Utility::Point> pointsInRange = getPointsInRange(position, i);
        std::vector<std::shared_ptr<Gameplay::Pokemon>> pokemonInRange;
        
        for (auto iter = pointsInRange.begin(); iter != pointsInRange.end(); iter++)
        {
            std::shared_ptr<Gameplay::Pokemon> pokemon = getPokemonFromPosition(*iter);
            if (pokemon != NULL && pokemon->alliance != alliance)
            {
                return i;
            }
        }
	}

    return -1;
}

// Draw the current world.
void Gameplay::World::drawWorld()
{
    GUI::drawWorld(_map, _cursorPos);
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

// Get the size of the map as a Point(width, height) value.
Utility::Point Gameplay::World::getMapSize()
{
    return Utility::Point(_map.size(), _map[0].size());
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

// Return the terrain at the given coordinate.
Gameplay::Terrain Gameplay::World::getTerrainFromPosition(Utility::Point position)
{
    return _map[position.x][position.y].terrain;
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
    setCursorPosIfInRange(startingPosition,
                          Utility::Point(_cursorPos.x, _cursorPos.y + 1),
                          maxRange);
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
    setCursorPosIfInRange(startingPosition,
                          Utility::Point(_cursorPos.x - 1, _cursorPos.y),
                          maxRange);
}

// Move the cursor to the right, if it doesn't go outside the map.
void Gameplay::World::moveCursorRight()
{
    _cursorPos.x = State::Controller::moveRight(_cursorPos.x, _map.size() - 1);
}

// Move the cursor right, only if it stays in the map and doesn't go
// out of range from a starting position.
void Gameplay::World::moveCursorRightIfInRange(Utility::Point startingPosition, unsigned int maxRange)
{
    setCursorPosIfInRange(startingPosition,
                          Utility::Point(_cursorPos.x + 1, _cursorPos.y),
                          maxRange);
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
    setCursorPosIfInRange(startingPosition,
                          Utility::Point(_cursorPos.x, _cursorPos.y - 1),
                          maxRange);
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

// Call when the player starts their turn to call the onStartTurn function
// for each Pokemon.
void Gameplay::World::onStartPlayerTurn()
{
    for (unsigned int i = 0; i < _playerPokemon.size(); i++)
    {
        _playerPokemon[i]->onStartTurn();
    }

    for (unsigned int i = 0; i < _enemyPokemon.size(); i++)
    {
        _enemyPokemon[i]->onStartTurn();
    }
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

// Set the cursor's position to the target position, if it's within
// the range of the starting position.
void Gameplay::World::setCursorPosIfInRange(Utility::Point startingPosition,
                           Utility::Point targetPosition,
                           unsigned int maxRange)
{
    if (targetPosition.x >= _map.size() || targetPosition.y >= _map[0].size())
        return;

    if (targetPosition.distanceFrom(startingPosition) <= maxRange)
        _cursorPos = targetPosition;
}