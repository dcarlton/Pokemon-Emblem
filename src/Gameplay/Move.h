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
    unsigned int getBasePower();
    std::string getName();

private:
    unsigned int basePower;
    std::string name;
};

}


#endif