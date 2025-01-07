#include "file_logger.h"

FileLogger::FileLogger(const std::string& fileName,
                       std::shared_ptr<ILogFormatter> formatter,
                       const std::ios_base::openmode& openMode)
                       : _file(fileName, openMode), _formatter(formatter) {
    if (!_file.is_open()) {
        throw std::ios_base::failure("Failed to open log file: " + fileName);
    }
}

FileLogger::~FileLogger() {
    if (_file.is_open()) {
        _file.close();
    }
}

void FileLogger::log(LogType logType, const std::string& message) const {
    std::lock_guard<std::mutex> lock(_mutex);

    std::string formattedMessage = this->_formatter->format(logType, message);

    if (_file.is_open()) {
        _file << formattedMessage << std::endl;
    }
}
