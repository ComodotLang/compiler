#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>
#include "ilog_formatter.h"


std::string ILogFormatter::getCurrentTimestamp() const {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream timestamp;
    timestamp << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");

    return timestamp.str();
}
