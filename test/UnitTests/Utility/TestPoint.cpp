#include "catch.hpp"

#include "../src/Utility/Point.h"


TEST_CASE("Testing the Point utility class")
{
    SECTION("Testing the public API")
    {
        Utility::Point point(1, 2);
        CHECK(point.x == 1);
        CHECK(point.y == 2);
    }
}