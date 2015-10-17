#include <fstream>
#include <time.h>

#include "Log.h"

namespace
{
    std::ofstream logfile;
    const std::string logFilename = "log.txt";
}

// TODO: Cannot obtain write permissions
// TODO: initLog is called multiple times
// TODO: quitLog is called before initLog

void Utility::initLog()
{
    if (!logfile.is_open())
        logfile.open(logFilename);
}

void Utility::log(std::string message)
{
    if (!logfile.is_open())
        return;

    time_t timer = time(0);
    struct std::tm* now = localtime(&timer);
    logfile << now->tm_hour
            << ":"
            << now->tm_min
            << ":"
            << now->tm_sec
            << " - "
            << message
            << "\n";
    delete now;
}

void Utility::quitLog()
{
    logfile.close();
    logfile.clear();
}