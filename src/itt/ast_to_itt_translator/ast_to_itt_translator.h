#pragma once
#include "../../ast/ast.h"
#include "../itt.h"
#include <memory.h>
#include <optional>

class AstToIttTranslator : public IVisitor {
  private:
    std::unique_ptr<IttNode> _result;
  public:
    std::unique_ptr<IttNode> translate(INode& node);

    void visit(IntegerNode& node) override;
    void visit(FloatNode& node) override;
    void visit(IdentifierNode& node) override;
    void visit(BinaryOperationNode& node) override;
    void visit(VarDefNode& node) override;
    void visit(ReturnNode& node) override;
    void visit(BlockNode& node) override;
    void visit(FunctionNode& node) override;
    void visit(CallNode& node) override;
  
  private:
    IttBinaryOperation mapBinaryOperator(BinaryOperator op);
    IttType mapType(const std::string& typeStr);
};
