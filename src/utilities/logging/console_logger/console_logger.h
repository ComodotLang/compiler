#pragma once
#include <memory>

#include "../ilogger.h"
#include "../log_formatter/interface/ilog_formatter.h"
#include "../log_formatter/color_formatter/color_formatter.h"

class ConsoleLogger : public ILogger {
  public:
    ConsoleLogger(std::shared_ptr<ILogFormatter> formatter = std::make_shared<ColorFormatter>());
    void log(LogType logType, const std::string& message) const override;
  private:
    std::shared_ptr<ILogFormatter> _formatter;
};
