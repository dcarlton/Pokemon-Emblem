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

// Used for a bitwise flag to determine who a move can hit.
enum TARGET
{
    SELF = 1,
    ALLY = 2,
    ENEMY = 4
};

class Move
{
public:
    bool doesDamage;
    
    Move();
    Move(std::string name);
    bool alwaysHits();
    int calculateDamage(int attack, int defense);
    bool canTarget(std::shared_ptr<Pokemon> attacker, std::shared_ptr<Pokemon> defender);
    unsigned int getAccuracy();
    unsigned int getBasePower();
    std::string getName();
    unsigned int getRange();
    unsigned int getTarget();
    void runSideEffects(std::shared_ptr<Pokemon> attackingPokemon, std::shared_ptr<Pokemon> targetPokemon);

private:
    unsigned int _accuracy;
    bool _alwaysHits;
    unsigned int _basePower;
    std::string _damageType;  // Theoretically shouldn't be stringly typed, but it's a private value with one specific use, so ¯\_(ツ)_/¯
    std::string _name;
    unsigned int _range;
    unsigned int _target;
    std::vector<std::function<void(std::shared_ptr<Pokemon>, std::shared_ptr<Pokemon>)>> _sideEffects;

    void addTargetBoostSideEffect(Stat stat, int statBoost);
};

}


#endif