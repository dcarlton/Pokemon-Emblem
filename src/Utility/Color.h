#ifndef RGB_H
#define RGB_H

#include "Int.h"

namespace Utility
{

class Color
{
public:
    uint8 red = 0;
    uint8 green = 0;
    uint8 blue = 0;

    Color(uint8 r, uint8 g, uint8 b) {red = r; green = g; blue = b;}
};

}

#endif