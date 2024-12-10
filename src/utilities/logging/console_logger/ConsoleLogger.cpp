#include <iostream>

#include "../ILogger.h"
#include "ConsoleLogger.h"

ConsoleLogger::ConsoleLogger(std::shared_ptr<ILogFormatter> formatter) 
             : _formatter(formatter) {}

void ConsoleLogger::log(LogType logType, const std::string& message) const {
    std::string formattedMessage = this->_formatter->format(logType, message);
    std::cout << formattedMessage << std::endl;
}
