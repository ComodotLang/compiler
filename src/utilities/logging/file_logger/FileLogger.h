#pragma once
#include <fstream>
#include <string>
#include <mutex>
#include <memory>

#include "../ILogger.h"
#include "../log_formatter/interface/ILogFormatter.h"
#include "../log_formatter/default_formatter/DefaultFormatter.h"

class FileLogger : public ILogger {
public:
    FileLogger(const std::string& fileName,
               std::shared_ptr<ILogFormatter> formatter = std::make_shared<DefaultFormatter>(),
               const std::ios_base::openmode& openMode = std::ios::in);
    void log(LogType logType, const std::string& message) const override;
    ~FileLogger() override;

private:
    mutable std::ofstream _file;
    mutable std::mutex _mutex;
    std::shared_ptr<ILogFormatter> _formatter;
};
