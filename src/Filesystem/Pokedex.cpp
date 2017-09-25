#include <fstream>
#include <sstream>

#include "json.hpp"
#include "tinyxml2.h"

#include "../Utility/Log.h"
#include "Pokedex.h"


namespace
{
    std::shared_ptr<tinyxml2::XMLDocument> initLearnsetsFile()
    {
        std::shared_ptr<tinyxml2::XMLDocument> learnsetsFile = std::make_shared<tinyxml2::XMLDocument>();
        learnsetsFile->LoadFile("learnsets.xml");
        return learnsetsFile;
    }
    
    // Read info on every Pokemon from the file pokedex.json
    nlohmann::json initPokedex()
    {
        std::ifstream pokedexFile("pokedex.json");
        std::stringstream tempStream;
        tempStream << pokedexFile.rdbuf();
        return nlohmann::json::parse(tempStream.str());
    }

    std::shared_ptr<tinyxml2::XMLDocument> learnsetsFile = initLearnsetsFile();
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
    stats.catchRate = pokedex[name]["catchRate"];
    return stats;
}

// Get a Pokemon's base stats for its fully evolved form.
// If it has multiple evolutions, get the first form before
// the evolution line splits.
Filesystem::Pokedex::BaseStats Filesystem::Pokedex::getEvolvedBaseStats(std::string name)
{
    while (true)
    {
        int numEvolutions = pokedex[name]["evos"].size();
        if (numEvolutions != 1)
        {
            return getBaseStats(name);
        }
        
        name = pokedex[name]["evos"][0];
    }
}

std::array<std::shared_ptr<Gameplay::Move>, 4> Filesystem::Pokedex::getMoves(std::string pokemonName, unsigned int level)
{
    std::array<std::shared_ptr<Gameplay::Move>, 4> moves;

    const tinyxml2::XMLElement* pokemonElement = learnsetsFile->FirstChildElement("pokemon", "name", pokemonName.c_str());
    if (pokemonElement == NULL)
    {
        Utility::log("Couldn't find the Pokemon " + pokemonName + " in the learnsets file.");
        return moves;
    }

    int i = 0;
    for (const tinyxml2::XMLElement* moveElement = pokemonElement->FirstChildElement("levelup"); moveElement != NULL; moveElement = moveElement->NextSiblingElement("levelup"))
    {
        if (moveElement->UnsignedAttribute("level") > level)
        {
            break;
        }

        moves[i] = std::make_shared<Gameplay::Move>(moveElement->Attribute("move"));
        i = (++i) % 4;
    }

    return moves;
}


// Get a Pokemon's Pokedex number from the Pokedex.
unsigned int Filesystem::Pokedex::getNum(std::string name)
{
    return pokedex[name]["num"];
}