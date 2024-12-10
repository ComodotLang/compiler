#pragma once
#include <memory>

#include "../ILogger.h"
#include "../log_formatter/interface/ILogFormatter.h"
#include "../log_formatter/color_formatter/ColorFormatter.h"

class ConsoleLogger : public ILogger {
  public:
    ConsoleLogger(std::shared_ptr<ILogFormatter> formatter = std::make_shared<ColorFormatter>());
    void log(LogType logType, const std::string& message) const override;
  private:
    std::shared_ptr<ILogFormatter> _formatter;
};
