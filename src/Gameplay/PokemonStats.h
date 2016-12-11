#ifndef POKEMONSTATS_H
#define POKEMONSTATS_H


#include <string>

#include "PokemonEnum.h"


namespace Gameplay
{

class PokemonStats
{
public:
    PokemonStats();
    PokemonStats(std::string name, unsigned int level);
    int getAttack();
    int getCurrentHP();
    int getDefense();
    unsigned int getLevel();
    unsigned int getMaxHP();
    unsigned int getMovementRange();
    unsigned int getSkill();
    unsigned int getSpeed();
    void takeDamage(int damage);

private:
    int attack;
    int currentHP;
    int defense;
    unsigned int level;
    unsigned int maxHP;
    unsigned int movement;
    unsigned int skill;
    unsigned int speed;

    void levelUpNormalized(std::string name, unsigned int numLevels);
    unsigned int roundRandomly(double num);
    void setLevelOneStats(std::string name);
    void setMovementRange(unsigned int baseSpeed);
};

}


#endif