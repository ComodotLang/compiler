#pragma once
#include "../interface/ilog_formatter.h"

class DefaultFormatter : public ILogFormatter {
  public:
    std::string format(LogType logType, const std::string& message) const override;
};