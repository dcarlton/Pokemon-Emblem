#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>

#include "../Utility/Point.h"
#include "Pokemon.h"
#include "Tile.h"

namespace Gameplay
{


class World
{
public:
    World();
    void addPokemon(std::shared_ptr<Pokemon> pokemon, Utility::Point position);
    void drawWorld();
    Utility::Point getCursorPos();
    std::vector<Utility::Point> getEnemyPokemonPositions();
    std::vector<Utility::Point> getPointsInRange(Utility::Point startingPosition, uint32 range);
    std::shared_ptr<Pokemon> getPokemonFromPosition(Utility::Point position);
    std::shared_ptr<Pokemon> getPokemonUnderCursor();
    bool hasAllPlayerPokemonMoved();
    void moveCursorDown();
    void moveCursorDownIfInRange(Utility::Point startingPosition, unsigned int maxRange);
    void moveCursorLeft();
    void moveCursorLeftIfInRange(Utility::Point startingPosition, unsigned int maxRange);
    void moveCursorRight();
    void moveCursorRightIfInRange(Utility::Point startingPosition, unsigned int maxRange);
    void moveCursorUp();
    void moveCursorUpIfInRange(Utility::Point startingPosition, unsigned int maxRange);
    bool movePokemon(Utility::Point oldPosition, Utility::Point newPosition);
    void pokemonFainted(Utility::Point faintedPokemonPosition);
    void resetWhetherEnemyPokemonHaveMoved();
    void resetWhetherPlayerPokemonHaveMoved();
    void resetWhetherPokemonHaveMoved(std::vector<std::shared_ptr<Pokemon>> pokemans);
    bool setCursorPos(Utility::Point newPosition);

private:
    const GUI::Image _cursorImage = GUI::getImage(GUI::ImageEnum::GameplayCursor);
    Utility::Point _cursorPos;
    std::vector<std::shared_ptr<Pokemon>> _enemyPokemon;
    std::vector<std::vector<Gameplay::Tile>> _map;
    std::vector<std::shared_ptr<Pokemon>> _playerPokemon;

    void removePokemonFromList(std::shared_ptr<Gameplay::Pokemon> pokemon, std::vector<std::shared_ptr<Gameplay::Pokemon>> pokemonList);
};


}

#endif