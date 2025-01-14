#include <iostream>
#include "../utilities/logging/logger_manager/logger_manager.h"
#include "../utilities/logging/console_logger/console_logger.h"
#include "../utilities/logging/log_formatter/interface/ilog_formatter.h"
#include "../utilities/logging/log_formatter/default_formatter/default_formatter.h"
#include "../utilities/logging/file_logger/file_logger.h"

#include "../itt/ast_to_itt_translator/ast_to_itt_translator.h"
#include "../codegen_llvm/codegen.h"

#include "../lexer/lexer.h"

int main() {
    LoggerManager& loggerManager = LoggerManager::getInstance();
    std::shared_ptr<ILogger> consoleLogger = std::make_shared<ConsoleLogger>();
    std::shared_ptr<ILogFormatter> logFormatter = std::make_shared<DefaultFormatter>();
    loggerManager.addLogger(consoleLogger);


    return 0;
}
