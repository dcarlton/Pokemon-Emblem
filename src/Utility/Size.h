#ifndef SIZE_H
#define SIZE_H

#include <string>


namespace Utility
{

class Size
{
public:
    int height = 0;
    int width = 0;

    Size() {};
    Size(int widthArg, int heightArg) {height = heightArg; width = widthArg;}
    std::string to_string() {return std::to_string(width) + 'x' + std::to_string(height);}
};

}

#endif