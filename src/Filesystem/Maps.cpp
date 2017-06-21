#include <string.h>
#include <vector>

#include "tinyxml2.h"

#include "../Gameplay/Tile.h"
#include "Maps.h"


std::shared_ptr<Gameplay::World> Filesystem::CreateWorld()
{
    tinyxml2::XMLDocument levelFile;
    levelFile.LoadFile("resources/Maps/Tutorial.tmx");

    tinyxml2::XMLDocument terrainFile;
    terrainFile.LoadFile("resources/Tiles/Terrain.png");

    // GetText() returns a const char*, but strtok aka split can't
    // take a const char*.
    const char* constTerrainLayout = levelFile.FirstChildElement("map")->FirstChildElement("layer")->FirstChildElement("data")->GetText();
    char tempTerrainLayout[8192];
    std::strcpy(tempTerrainLayout, constTerrainLayout);
    char* terrainLayout = std::strtok(tempTerrainLayout, ",");
    terrainLayout; // TODO: Using this variable

    std::vector<std::vector<Gameplay::Tile>> map;
    int mapHeight = levelFile.FirstChildElement("map")->IntAttribute("height");
    int mapWidth = levelFile.FirstChildElement("map")->IntAttribute("width");

    for (int i = 0; i < mapWidth; i++)
    {
        std::vector<Gameplay::Tile> column;
        for (int j = 0; j < mapHeight; j++)
        {
            column.push_back(Gameplay::Tile());
        }

        map.push_back(column);
    }

    return std::make_shared<Gameplay::World>(map, Utility::Point(0, 0));
}