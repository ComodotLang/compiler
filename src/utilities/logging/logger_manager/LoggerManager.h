#pragma once
#include <memory>
#include <vector>
#include <mutex>

#include "../ILogger.h"

class LoggerManager {
  public:
    static LoggerManager& getInstance();
    void addLogger(std::shared_ptr<ILogger> logger);
    void log(LogType logType, const std::string& message);

  private:
    LoggerManager() = default;
    LoggerManager(const LoggerManager&) = delete;
    LoggerManager& operator=(const LoggerManager&) = delete;

    std::mutex _mutex;
    std::vector<std::shared_ptr<ILogger>> _loggers;
};
