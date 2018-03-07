#include <string.h>
#include <vector>

#include "tinyxml2.h"

#include "../GUI/GUI.h"
#include "../Utility/Log.h"
#include "Maps.h"
#include "../Gameplay/Tile.h"


namespace
{
    // Add all of the Pokemon in the level file to the world.
    void addPokemonToWorld(std::shared_ptr<Gameplay::World> world, tinyxml2::XMLDocument* levelFile)
    {
        tinyxml2::XMLDocument pokemonFile;
        pokemonFile.LoadFile("resources/Maps/Pokemon.tsx");

        int tileWidth = levelFile->FirstChildElement("map")->IntAttribute("tilewidth");
        int tileHeight = levelFile->FirstChildElement("map")->IntAttribute("tileheight");

        const tinyxml2::XMLElement* pokemonElement = levelFile->FirstChildElement("map")->FirstChildElement("objectgroup", "name", "Pokemon")->FirstChildElement("object");
        for (; pokemonElement != NULL; pokemonElement = pokemonElement->NextSiblingElement("object"))
        {
            int pokemonId = pokemonElement->IntAttribute("gid") - 3;
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
    }

    // Fill the world with terrain based on the given level file.
    void addTerrainToMap(std::vector<std::vector<Gameplay::Tile>>* map, tinyxml2::XMLDocument* levelFile, int mapWidth, int mapHeight)
    {
        tinyxml2::XMLDocument terrainFile;
        terrainFile.LoadFile("resources/Maps/Terrain.tsx");

        const char* formattedTerrain = levelFile->FirstChildElement("map")->FirstChildElement("layer", "name", "Terrain")->FirstChildElement("data")->GetText();
        char* terrain = const_cast<char*>(formattedTerrain);

        // strtok is sort of like String.Split, but it only returns the first result.
        // To get the next result, you have to call strtok again, passing NULL instead of the original char*.
        terrain = std::strtok(terrain, ",\n");

        // The number of columns in the Terrain.tsx Tiled file.
        int numTerrainColumns = terrainFile.FirstChildElement("tileset", "name", "Terrain")->IntAttribute("columns");
        for (int y = 0; y < mapHeight; y++)
        {
            for (int x = 0; x < mapWidth; x++)
            {
                int terrainID = atoi(terrain) - 1;  // Magic number due to Tiled's ID not starting at 0.
                const tinyxml2::XMLElement* properties = terrainFile.FirstChildElement("tileset", "name", "Terrain")->FirstChildElement("tile", "id", std::to_string(terrainID).c_str())->FirstChildElement("properties");

                Gameplay::Tile tile;
                Utility::Point imageIndex = Utility::Point(terrainID % numTerrainColumns, terrainID / numTerrainColumns);
                int avoid = properties->FirstChildElement("property", "name", "Avoid")->IntAttribute("value");
                int defense = properties->FirstChildElement("property", "name", "Defense")->IntAttribute("value");
                tile.terrain = Gameplay::Terrain(imageIndex, avoid, defense);
                (*map)[x].push_back(tile);

                // See above comment for what strtok is.
                terrain = std::strtok(NULL, ",\n");
            }
        }
    }

    // Create an empty world with a bunch of empty columns.
    std::vector<std::vector<Gameplay::Tile>> createEmptyMap(int mapWidth)
    {
        std::vector<std::vector<Gameplay::Tile>> map;
        for (int i = 0; i < mapWidth; i++)
        {
            map.push_back(std::vector<Gameplay::Tile>());
        }

        return map;
    }
}

// Creates a world based on the tutorial file.
// Should be easy to convert to take any Tiled file.
std::shared_ptr<Gameplay::World> Filesystem::createWorld()
{
    tinyxml2::XMLDocument levelFile;
    levelFile.LoadFile("resources/Maps/Level1.tmx");

    int mapHeight = levelFile.FirstChildElement("map")->IntAttribute("height");
    int mapWidth = levelFile.FirstChildElement("map")->IntAttribute("width");

    std::vector<std::vector<Gameplay::Tile>> map = createEmptyMap(mapWidth);
    addTerrainToMap(&map, &levelFile, mapWidth, mapHeight);

    std::shared_ptr<Gameplay::World> world = std::make_shared<Gameplay::World>(map, Utility::Point(0, 0));
    addPokemonToWorld(world, &levelFile);
    return world;
}