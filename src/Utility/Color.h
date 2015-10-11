#ifndef RGB_H
#define RGB_H

#include "Int.h"

namespace Utility
{

class Color
{
public:
    uint8 red;
    uint8 green;
    uint8 blue;

    Color(uint8 r, uint8 g, uint8 b) {red = r; green = g; blue = b;}
};

}

#endif