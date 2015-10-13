#ifndef POINT_H
#define POINT_H

#include "Int.h"

// TODO: Namespace Point

class Point
{
public:
    Point(uint32 xPos, uint32 yPos) {x = xPos; y = yPos;}
    uint32 x = 0;
    uint32 y = 0;
};

#endif