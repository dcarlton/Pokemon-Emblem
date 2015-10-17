#include "catch.hpp"

#include "../src/Utility/Size.h"

TEST_CASE("Testing the Size utility class")
{
    SECTION("Testing converting to a string")
    {
        Utility::Size size(1, 1);
        REQUIRE(size.to_string() == "1x1");
    }
}