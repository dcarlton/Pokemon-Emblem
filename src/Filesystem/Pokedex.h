#ifndef POKEDEX_H
#define POKEDEX_H


#include <array>
#include <memory>
#include <string>

#include "../Gameplay/Move.h"


namespace Filesystem
{

namespace Pokedex
{
    struct BaseStats
    {
        unsigned int hp;
        unsigned int attack;
        unsigned int defense;
        unsigned int spAttack;
        unsigned int spDefense;
        unsigned int speed;
        unsigned int catchRate;
    };

    BaseStats getBaseStats(std::string name);
    BaseStats getEvolvedBaseStats(std::string name);
    std::array<std::shared_ptr<Gameplay::Move>, 4> getMoves(std::string pokemonName, unsigned int level);
    unsigned int getNum(std::string name);
}

}


#endif