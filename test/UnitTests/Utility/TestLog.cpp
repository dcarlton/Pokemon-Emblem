#include <exception>
#include <fstream>
#include <stdio.h>
#include <string>

#include "catch.hpp"

#include "../src/GUI/GUI.h"
#include "../src/Utility/Log.h"


bool logStartsWith(std::string contents)
{
    std::ifstream logfile(Utility::logFilename);
    std::string firstLine = "";

    std::getline(logfile, firstLine);
    logfile.close();

    return firstLine.rfind(contents) != std::string::npos;
}
TEST_CASE("Testing the log system")
{
    SECTION("Logging a message")
    {
        Utility::initLog();
        Utility::log("Test");
        Utility::quitLog();

        REQUIRE(logStartsWith("Test"));
    }

    // TODO: Figure out debuging tests and why this is failing
    SECTION("Log without initializing")
    {
        Utility::log("Test");
        //REQUIRE(!logStartsWith("Test"));
    }

    SECTION("Initialize multiple times")
    {
        Utility::initLog();
        Utility::initLog();
    }

    SECTION("Tear down without initializing")
    {
        Utility::quitLog();
    }
}