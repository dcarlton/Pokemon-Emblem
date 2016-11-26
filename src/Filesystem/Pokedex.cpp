#include <fstream>
#include <sstream>

#include "json.hpp"

#include "Pokedex.h"


namespace
{
    // Read info on every Pokemon from the file pokedex.json
    nlohmann::json initPokedex()
    {
        std::ifstream pokedexFile("../pokedex.json");
        std::stringstream tempStream;
        tempStream << pokedexFile.rdbuf();
        return nlohmann::json::parse(tempStream.str());
    }

    nlohmann::json pokedex = initPokedex();
}

// Get a Pokemon's base stats from the Pokedex.
Filesystem::Pokedex::BaseStats Filesystem::Pokedex::getBaseStats(std::string name)
{
    BaseStats stats;
    stats.hp = pokedex[name]["baseStats"]["hp"];
    stats.attack = pokedex[name]["baseStats"]["atk"];
    stats.defense = pokedex[name]["baseStats"]["def"];
    stats.spAttack = pokedex[name]["baseStats"]["spa"];
    stats.spDefense = pokedex[name]["baseStats"]["spd"];
    stats.speed = pokedex[name]["baseStats"]["spe"];
    return stats;
}

// Get a Pokemon's Pokedex number from the Pokedex.
unsigned int Filesystem::Pokedex::getNum(std::string name)
{
    return pokedex[name]["num"];
}