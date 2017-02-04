#ifndef MOVE_H
#define MOVE_H


#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "StatEnum.h"


namespace Gameplay
{

class Pokemon;

class Move
{
public:
    bool doesDamage;
    
    Move();
    Move(std::string name);
    unsigned int getAccuracy();
    unsigned int getBasePower();
    std::string getName();
    unsigned int getRange();
    void runSideEffects(std::shared_ptr<Pokemon> attackingPokemon, std::shared_ptr<Pokemon> targetPokemon);

private:
    unsigned int _accuracy;
    unsigned int _basePower;
    std::string _name;
    unsigned int _range;
    std::vector<std::function<void(std::shared_ptr<Pokemon>, std::shared_ptr<Pokemon>)>> _sideEffects;

    void addTargetBoostSideEffect(Stat stat, int statBoost);
};

}


#endif