#ifndef MOVE_H
#define MOVE_H


#include <string>


namespace Gameplay
{

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

private:
    unsigned int _accuracy;
    unsigned int _basePower;
    std::string _name;
    unsigned int _range;
};

}


#endif