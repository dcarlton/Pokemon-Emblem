#include "Point.h"


Utility::Point::Point()
{
    x = 0;
    y = 0;
}

Utility::Point::Point(uint32 xPos, uint32 yPos)
{
    x = xPos;
    y = yPos;
}

Utility::Point Utility::Point::operator=(const Utility::Point& rhs)
{
    x = rhs.x;
    y = rhs.y;
    return rhs;
}

bool Utility::Point::operator==(const Utility::Point& rhs)
{
    return x == rhs.x && y == rhs.y;
}

std::string Utility::Point::to_string()
{
    return std::to_string(x) + "," + std::to_string(y);
}
