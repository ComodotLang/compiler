#pragma once
#include "../interface/ILogFormatter.h"

class DefaultFormatter : public ILogFormatter {
  public:
      std::string format(LogType logType, const std::string& message) const override;
};