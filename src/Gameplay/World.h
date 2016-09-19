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
    std::shared_ptr<Pokemon> getPokemonFromPosition(Utility::Point position);
    std::shared_ptr<Pokemon> getPokemonUnderCursor();
    bool hasAllPlayerPokemonMoved();
    void moveCursorDown();
    void moveCursorLeft();
    void moveCursorRight();
    void moveCursorUp();
    void movePokemon(Utility::Point oldPosition, Utility::Point newPosition);
    void resetWhetherPlayerPokemonHaveMoved();
    bool setCursorPos(Utility::Point newPosition);

private:
    const GUI::Image _cursorImage = GUI::getImage(GUI::ImageEnum::GameplayCursor);
    Utility::Point _cursorPos;
    std::vector<std::shared_ptr<Pokemon>> _enemyPokemon;
    std::vector<std::vector<Gameplay::Tile>> _map;
    std::vector<std::shared_ptr<Pokemon>> _playerPokemon;
};


}

#endif