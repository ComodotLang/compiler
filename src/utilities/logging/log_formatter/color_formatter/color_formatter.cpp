#include <iomanip>
#include <sstream>
#include "color_formatter.h"

std::string ColorFormatter::format(LogType logType, const std::string& message) const {
    std::ostringstream formattedMessage;
    std::string timestamp = this->getCurrentTimestamp();
    std::string logLevel = LogTypeHelper::toString(logType);
    std::string color = this->getLogLevelColorCode(logType);
    formattedMessage << "[" << timestamp << "]" 
                     << "[" << color + logLevel + "\033[0m" << "]: "
                     << message;

    return formattedMessage.str();
}


std::string ColorFormatter::getLogLevelColorCode(LogType logType) const {
    switch (logType) {
        case LogType::INFO: return "\033[0m";
        case LogType::DEBUG: return "\033[0;34m";
        case LogType::WARN: return "\033[0;33m";
        case LogType::ERR: return "\033[1;31m";
        default: return "\033[0m";
    }
}
