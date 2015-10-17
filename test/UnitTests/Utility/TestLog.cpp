#include <exception>
#include <fstream>
#include <stdio.h>
#include <string>

#include "catch.hpp"

#include "../src/GUI/GUI.h"
#include "../src/Utility/Log.h"

TEST_CASE("Testing the log system")
{
    SECTION("Logging a message")
    {
        Utility::initLog();
        Utility::log("Test");
        Utility::quitLog();

        std::ifstream logfile("log.txt");
        std::string temp = "";

        std::getline(logfile, temp);
        logfile.close();
        REQUIRE(temp.rfind("Test") != std::string::npos);
    }

    SECTION("Log without initializing")
    {
        Utility::log("Test");
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