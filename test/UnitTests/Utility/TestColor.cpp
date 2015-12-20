#include "catch.hpp"

#include "../src/Utility/Color.h"


TEST_CASE("Testing the Color utility class")
{
    SECTION("Testing the public API")
    {
        Utility::Color color(1, 2, 3);
        CHECK(color.red == 1);
        CHECK(color.green == 2);
        CHECK(color.blue == 3);
    }
}