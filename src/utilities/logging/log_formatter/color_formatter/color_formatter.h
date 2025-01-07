#pragma once
#include "../interface/ilog_formatter.h"

class ColorFormatter : public ILogFormatter {
  public:
      std::string format(LogType logType, const std::string& message) const override;
  private:
      std::string getLogLevelColorCode(LogType logType) const;
};