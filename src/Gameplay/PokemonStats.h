#ifndef POKEMONSTATS_H
#define POKEMONSTATS_H


#include <string>

#include "PokemonEnum.h"
#include "StatEnum.h"


namespace Gameplay
{

class PokemonStats
{
public:
    PokemonStats();
    PokemonStats(std::string name, unsigned int level);
    unsigned int getAccuracy();
    int getAttack();
    int getCurrentHP();
    int getDefense();
    unsigned int getEvasion();
    unsigned int getLevel();
    unsigned int getLuck();
    unsigned int getMaxHP();
    unsigned int getMovementRange();
    unsigned int getSkill();
    int getSpeed();
    void onStartTurn();
    void setStatBoost(Stat stat, int statBoost);
    void takeDamage(int damage);

private:
    int attack;
    int attackBoost;
    unsigned int attackBoostDuration;
    int currentHP;
    int defense;
    int defenseBoost;
    unsigned int defenseBoostDuration;
    unsigned int level;
    unsigned int luck;
    unsigned int maxHP;
    unsigned int movement;
    unsigned int skill;
    int speed;
    int speedBoost;
    unsigned int speedBoostDuration;

    void levelUpNormalized(std::string name, unsigned int numLevels);
    unsigned int roundRandomly(double num);
    void setLevelOneStats(std::string name);
    void setMovementRange(unsigned int baseSpeed);
    void setStatBoost(int* currentStatBoost, const int newStatBoost, unsigned int* statBoostDuration);
};

}


#endif