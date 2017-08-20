#include <string.h>
#include <vector>

#include "tinyxml2.h"

#include "../Gameplay/Tile.h"
#include "Maps.h"
#include "../Utility/Log.h"


std::shared_ptr<Gameplay::World> Filesystem::CreateWorld()
{
    tinyxml2::XMLDocument levelFile;
    levelFile.LoadFile("resources/Maps/Tutorial.tmx");

    std::vector<std::vector<Gameplay::Tile>> map;
    int mapHeight = levelFile.FirstChildElement("map")->IntAttribute("height");
    int mapWidth = levelFile.FirstChildElement("map")->IntAttribute("width");
    int tileWidth = levelFile.FirstChildElement("map")->IntAttribute("tilewidth");
    int tileHeight = levelFile.FirstChildElement("map")->IntAttribute("tileheight");
    for (int i = 0; i < mapWidth; i++)
    {
        std::vector<Gameplay::Tile> column;
        for (int j = 0; j < mapHeight; j++)
        {
            column.push_back(Gameplay::Tile());
        }

        map.push_back(column);
    }

    tinyxml2::XMLDocument pokemonFile;
    pokemonFile.LoadFile("resources/Maps/Pokemon.tsx");

    std::shared_ptr<Gameplay::World> world = std::make_shared<Gameplay::World>(map, Utility::Point(0, 0));

    const tinyxml2::XMLElement* pokemonElement = levelFile.FirstChildElement("map")->FirstChildElement("objectgroup", "name", "Pokemon")->FirstChildElement("object");
    for (; pokemonElement != NULL; pokemonElement = pokemonElement->NextSiblingElement("object"))
    {
        int pokemonId = pokemonElement->IntAttribute("gid") - 2;
        int pokemonXPosition = pokemonElement->IntAttribute("x") / tileWidth;
        int pokemonYPosition = (pokemonElement->IntAttribute("y") - 1) / tileHeight;
        int pokemonLevel = pokemonElement->FirstChildElement("properties")->FirstChildElement("property", "name", "Level")->IntAttribute("value");
        Gameplay::AllianceEnum pokemonAlliance = static_cast<Gameplay::AllianceEnum>(pokemonElement->FirstChildElement("properties")->FirstChildElement("property", "name", "Alliance")->IntAttribute("value"));
        char buffer[10];
        const char* pokemonName = pokemonFile.FirstChildElement("tileset")
                                            ->FirstChildElement("tile", "id", itoa(pokemonId, buffer, 10))
                                            ->FirstChildElement("properties")
                                            ->FirstChildElement("property", "name", "Name")
                                            ->Attribute("value");
        
        std::shared_ptr<Gameplay::Pokemon> pokemon = std::make_shared<Gameplay::Pokemon>(pokemonName, pokemonLevel, pokemonAlliance);
        world->addPokemon(pokemon, Utility::Point(pokemonXPosition, pokemonYPosition));
    }

    return world;
}