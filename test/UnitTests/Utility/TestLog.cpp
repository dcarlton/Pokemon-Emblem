#include <fstream>
#include <string>

#include "catch.hpp"

#include "../src/Utility/Log.h"

TEST_CASE("Logging a message")
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