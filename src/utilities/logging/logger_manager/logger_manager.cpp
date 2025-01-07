#include "logger_manager.h"
#include <stdexcept>

LoggerManager& LoggerManager::getInstance() {
    static LoggerManager instance;
    return instance;
}

void LoggerManager::addLogger(std::shared_ptr<ILogger> logger) {
    std::lock_guard<std::mutex> lock(this->_mutex);
    this->_loggers.push_back(logger);
}

void LoggerManager::log(LogType logType, const std::string& message) {
    std::lock_guard<std::mutex> lock(this->_mutex);

    for (auto& logger : this->_loggers) {
        logger->log(logType, message);
    }
}
