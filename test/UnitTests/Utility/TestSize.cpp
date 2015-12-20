#include "catch.hpp"

#include "../src/Utility/Size.h"

TEST_CASE("Testing the Size utility class")
{
    SECTION("Test the basic public API")
    {
        Utility::Size size(1, 1);
        REQUIRE(size.height == 1);
        REQUIRE(size.width == 1);
    }

    SECTION("Testing converting to a string")
    {
        Utility::Size size(1, 1);
        REQUIRE(size.to_string() == "1x1");
    }
}