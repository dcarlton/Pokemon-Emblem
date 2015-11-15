#include "catch.hpp"

#include "../src/State/Controller/MoveUtils.h"


namespace State
{
namespace Controller
{


TEST_CASE("Testing the movement related functions for states")
{
    SECTION("Downward movement")
    {
        REQUIRE(moveDown(0, 5) == 1);
    }

    SECTION("Downward movement attempted out of bounds")
    {
        REQUIRE(moveDown(0, 0) == 0);
    }

    SECTION("Downward movement attempted while out of bounds")
    {
        REQUIRE_THROWS_AS(moveDown(1, 0), OutOfBoundsException);
    }

    SECTION("Downward movement with negative numbers")
    {
        REQUIRE(moveDown(-3, -1) == -2);
    }


    SECTION("Leftward movement")
    {
        REQUIRE(moveLeft(1, 0) == 0);
    }

    SECTION("Leftward movement attempted out of bounds")
    {
        REQUIRE(moveLeft(0, 0) == 0);
    }

    SECTION("Leftward movement attempted while out of bounds")
    {
        REQUIRE_THROWS_AS(moveLeft(0, 1), OutOfBoundsException);
    }

    SECTION("Leftward movement with negative numbers")
    {
        REQUIRE(moveLeft(-1, -3) == -2);
    }


    SECTION("Rightward movement")
    {
        REQUIRE(moveRight(0, 5) == 1);
    }

    SECTION("Rightward movement attempted out of bounds")
    {
        REQUIRE(moveRight(0, 0) == 0);
    }

    SECTION("Rightward movement attempted while out of bounds")
    {
        REQUIRE_THROWS_AS(moveRight(1, 0), OutOfBoundsException);
    }

    SECTION("Rightward movement with negative numbers")
    {
        REQUIRE(moveRight(-3, -1) == -2);
    }


    SECTION("Upward movement")
    {
        REQUIRE(moveUp(1, 0) == 0);
    }

    SECTION("Upward movement attempted out of bounds")
    {
        REQUIRE(moveUp(0, 0) == 0);
    }

    SECTION("Upward movement attempted while out of bounds")
    {
        REQUIRE_THROWS_AS(moveUp(0, 1), OutOfBoundsException);
    }

    SECTION("Upward movement with negative numbers")
    {
        REQUIRE(moveUp(-1, -3) == -2);
    }
}


}
}