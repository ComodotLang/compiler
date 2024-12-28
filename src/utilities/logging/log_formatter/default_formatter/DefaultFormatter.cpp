#include <iomanip>
#include <sstream>
#include "DefaultFormatter.h"

std::string DefaultFormatter::format(LogType logType, const std::string& message) const {
    std::ostringstream formattedMessage;
    std::string timestamp = this->getCurrentTimestamp();
    std::string logLevel = LogTypeHelper::toString(logType);
    formattedMessage << "[" << timestamp << "]" 
                     << "[" << logLevel<< "]: "
                     << message;

    return formattedMessage.str();
}
