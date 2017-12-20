#ifndef POINT_H
#define POINT_H

#include <string>
#include <vector>

#include "Int.h"


namespace Utility
{

class Point
{
public:
    Point();
    Point(uint32 xPos, uint32 yPos);
    uint32 x = 0;
    uint32 y = 0;

    Point operator=(const Point& rhs);
    bool operator==(const Point& rhs);
    bool operator!=(const Point& rhs);
    Point operator+(const Point& rhs);
    Point operator+=(const Point& rhs);
    Point operator-(const Point& rhs);
    Point operator-=(const Point& rhs);
    Point operator*(const uint32 rhs);

    uint32 distanceFrom(const Point& rhs);
    std::vector<Point> getPointsWithinDistance(uint32 distance);
    std::string to_string();
};

}

#endif
