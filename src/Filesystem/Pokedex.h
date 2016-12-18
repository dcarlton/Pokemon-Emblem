#ifndef POKEDEX_H
#define POKEDEX_H


#include <string>


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
    unsigned int getNum(std::string name);
}

}


#endif