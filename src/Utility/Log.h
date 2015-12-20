#include <string>

namespace Utility
{
    const std::string logFilename = "log.txt";

    void initLog();
    void log(std::string message);
    void quitLog();
};