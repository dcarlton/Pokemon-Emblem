#include <cmath>

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

bool Utility::Point::operator!=(const Utility::Point& rhs)
{
    return !(*this == rhs);
}

// Subtraction. Will probably fail spectacularly if the second
// point is larger.
Utility::Point Utility::Point::operator-(const Point& rhs)
{
    return Utility::Point(x - rhs.x, y - rhs.y);
}

Utility::Point Utility::Point::operator-=(const Point& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Utility::Point Utility::Point::operator*(const uint32 rhs)
{
    return Utility::Point(x * rhs, y * rhs);
}

// Returns the distance from this point to the parameter.
uint32 Utility::Point::distanceFrom(const Utility::Point& rhs)
{
    return std::abs((int)(x - rhs.x)) + std::abs((int)(y - rhs.y));
}

// Return all points within the given distance from this point.
// TODO: Make it less bad. Written on 10/24/16, I'm guessing I
// won't actually get around to it :)
std::vector<Utility::Point> Utility::Point::getPointsWithinDistance(uint32 distance)
{
    std::vector<Utility::Point> pointsWithinDistance;

    for (int i = (int)x - (int)distance; i <= (int)x + (int)distance; i++)
    {
        if (i < 0)
            continue;

        for (int j = (int)y - (int)distance; j <= (int)y + (int)distance; j++)
        {
            Utility::Point possiblePoint = Utility::Point(i, j);
            if (j < 0 || distanceFrom(possiblePoint) > distance)
                continue;

            pointsWithinDistance.push_back(possiblePoint);
        }
    }

    return pointsWithinDistance;
}

std::string Utility::Point::to_string()
{
    return std::to_string(x) + "," + std::to_string(y);
}
