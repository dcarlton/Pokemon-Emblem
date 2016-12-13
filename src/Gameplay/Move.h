#ifndef MOVE_H
#define MOVE_H


#include <string>


namespace Gameplay
{

class Move
{
public:
    Move();
    Move(std::string name);
    unsigned int getAccuracy();
    unsigned int getBasePower();
    std::string getName();

private:
    unsigned int _accuracy;
    unsigned int _basePower;
    std::string _name;
};

}


#endif