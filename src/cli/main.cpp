#include <iostream>
#include "../utilities/logging/logger_manager/logger_manager.h"
#include "../utilities/logging/console_logger/console_logger.h"
#include "../utilities/logging/log_formatter/interface/ilog_formatter.h"
#include "../utilities/logging/log_formatter/default_formatter/default_formatter.h"
#include "../utilities/logging/file_logger/file_logger.h"

#include "../itt/itt.h"
#include "../codegen_llvm/codegen.h"

int main() {
    LoggerManager& loggerManager = LoggerManager::getInstance();
    std::shared_ptr<ILogger> consoleLogger = std::make_shared<ConsoleLogger>();
    std::shared_ptr<ILogFormatter> logFormatter = std::make_shared<DefaultFormatter>();
    loggerManager.addLogger(consoleLogger);
    loggerManager.log(LogType::ERR, "ABOBA");


    // std::unique_ptr<IttIntegerNode> rC = std::make_unique<IttIntegerNode>(0);

    // std::unique_ptr<IttReturnNode> rN = std::make_unique<IttReturnNode>(std::make_optional(std::move(rC)));

    // std::vector<std::unique_ptr<IttNode>> statements; 
    // statements.push_back(std::move(rN));            

    // std::unique_ptr<IttBlockNode> bb = std::make_unique<IttBlockNode>(std::move(statements));

    // std::vector<std::pair<std::string, IttType>> parameters;

    // std::unique_ptr<IttFunctionNode> fM = std::make_unique<IttFunctionNode>(
    //     "main",                      
    //     std::move(parameters),      
    //     std::move(bb),              
    //     IttType(IttType::INT)        
    // );

    // ModuleCodegenCtx ctx = ModuleCodegenCtx();

    // CodegenVisitor visitor = CodegenVisitor(ctx);

    // fM.get()->accept(visitor);

    // visitor.getBuildedModule().get()->print(llvm::outs(), nullptr);

    // return 0;
}
