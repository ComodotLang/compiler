#include <iostream>
#include "../utilities/logging/logger_manager/LoggerManager.h"
#include "../utilities/logging/console_logger/ConsoleLogger.h"
#include "../utilities/logging/log_formatter/interface/ILogFormatter.h"
#include "../utilities/logging/log_formatter/default_formatter/DefaultFormatter.h"
#include "../utilities/logging/file_logger/FileLogger.h"

int main() {
    LoggerManager& loggerManager = LoggerManager::getInstance();
    std::shared_ptr<ILogger> consoleLogger = std::make_shared<ConsoleLogger>();
    std::shared_ptr<ILogFormatter> logFormatter = std::make_shared<DefaultFormatter>();
    loggerManager.addLogger(consoleLogger);


    loggerManager.log(LogType::ERR, "ABOBA");

    return 0;
}
