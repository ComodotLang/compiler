#pragma once
#include <string>

enum class LogType {
    INFO,
    DEBUG,
    WARN,
    ERR,
};

class ILogger {
  public:
    virtual void log(LogType logType, const std::string& message) const = 0;
    virtual ~ILogger() = default;
};

class LogTypeHelper {
  public:
    static std::string toString(LogType logType) {
        switch (logType) {
          case LogType::INFO: return "INFO";
          case LogType::DEBUG: return "DEBUG";
          case LogType::WARN: return "WARN";
          case LogType::ERR: return "ERR";
          default: return "UNKNOWN";
        }
    }
};