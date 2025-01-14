#include <stdexcept>

#include "ast_to_itt_translator.h"


std::shared_ptr<IttNode> AstToIttTranslator::translate(INode& node) {
    node.accept(*this);
    return _result;
}

void AstToIttTranslator::visit(IntegerNode& node) {
    this->_result = std::make_shared<IttIntegerNode>(node.getValue());
}

void AstToIttTranslator::visit(FloatNode& node) {
    this->_result = std::make_shared<IttFloatNode>(node.getValue());
}

void AstToIttTranslator::visit(IdentifierNode& node) {
    this->_result = std::make_shared<IttIdentifierNode>(node.getName());
}

void AstToIttTranslator::visit(BinaryOperationNode& node) {
    auto lhs = this->translate(node.getLhs());
    auto rhs = this->translate(node.getRhs());

    _result = std::make_shared<IttBinaryOperationNode>(
        lhs, rhs, mapBinaryOperator(node.getOp()));
}

void AstToIttTranslator::visit(VarDefNode& node) {
    auto content = this->translate(node.getContent());
    _result = std::make_shared<IttVariableNode>(node.getName(), content);
}

void AstToIttTranslator::visit(ReturnNode& node) {
    if (auto retDataOpt = node.getRetData()) {
        auto retData = this->translate(**retDataOpt);
        this->_result = std::make_shared<IttReturnNode>(retData);
    } else {
        this->_result = std::make_shared<IttReturnNode>(nullptr);
    }
}

void AstToIttTranslator::visit(BlockNode& node) {
    std::vector<std::shared_ptr<IttNode>> statements;

    for (const auto& astNode : node.getNodes()) {
        statements.push_back(this->translate(*astNode));
    }

    this->_result = std::make_shared<IttBlockNode>(statements);
}

void AstToIttTranslator::visit(FunctionNode& node) {
    std::vector<std::pair<std::string, IttType>> parameters;

    for (const auto& arg : node.getArgs()) {
        std::string argName = std::get<0>(arg);
        std::string argType = std::get<1>(arg);
        IttType type = mapType(argType);

        parameters.emplace_back(argName, type);
    }

    auto body = this->translate(node.getBody());
    IttType returnType = mapType(node.getReturnType());
    _result = std::make_shared<IttFunctionNode>(
        node.getName(), parameters, body);
}

void AstToIttTranslator::visit(CallNode& node) {

}

IttBinaryOperation AstToIttTranslator::mapBinaryOperator(BinaryOperator op) {
    switch (op) {
            case BinaryOperator::ADD: return IttBinaryOperation::ADD;
            case BinaryOperator::SUB: return IttBinaryOperation::SUB;
            case BinaryOperator::DIV: return IttBinaryOperation::DIV;
            case BinaryOperator::MUL: return IttBinaryOperation::MUL;
    }
    throw std::runtime_error("Unknown BinaryOperator");
}

IttType AstToIttTranslator::mapType(const std::string& typeStr) {
    if (typeStr == "int") {
        return IttType(IttType::INT);
    } else if (typeStr == "float") {
        return IttType(IttType::FLOAT);
    } else if (typeStr == "void") {
        return IttType(IttType::VOID);
    } else if (typeStr == "bool") {
        return IttType(IttType::BOOL);
    } else if (typeStr == "char") {
        return IttType(IttType::CHAR);
    } else {
        return IttType(IttType::UNRESOLVED);
    }
}