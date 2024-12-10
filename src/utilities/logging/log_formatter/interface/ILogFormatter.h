#pragma once
#include <string>

#include "../../ILogger.h"

class ILogFormatter {
  public:
    virtual std::string format(LogType logType, const std::string& message) const = 0;
    virtual std::string getCurrentTimestamp() const;
    virtual ~ILogFormatter() = default;
};
