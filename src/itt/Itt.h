#pragma once
#include <memory>
#include <vector>

#include "IttType.h"

class IttNode {
  protected:
    IttType _type;

  public:
    explicit IttNode(IttType type) : _type(type) {}
    virtual ~IttNode() = default;

    IttType getType() const { return _type; }

    virtual void accept(class IttVisitor& visitor) = 0;
};

class IttVisitor {
  public:
    virtual void visit(class IttLiteralNode& node) = 0;
    virtual void visit(class IttBinaryOperationNode& node) = 0;
    virtual void visit(class IttVariableNode& node) = 0;
    virtual void visit(class IttFunctionNode& node) = 0;
    virtual void visit(class IttBlockNode& node) = 0;
};

enum class IttVisibility {
    EXTERN,
    PUBLIC,
    PRIVATE
};

class ITTIntegerNode : public IttNode {
  int _value;

  public:
    ITTIntegerNode(int value) : IttNode(IttType(IttType::INT)), _value(value) {}

    int getValue() const { return _value; }
};

enum class IttBinaryOperation {
    ADD,
    SUB,
    MUL,
    DIV,
    AND,
    OR,
    LESS_THEN,
    GREATER_THEN,
    EQUALS
};

class IttBinaryOperationNode : public IttNode {
    std::unique_ptr<IttNode> _lhs;
    std::unique_ptr<IttNode> _rhs;
    IttBinaryOperation _op;

  public:
    IttBinaryOperationNode(
        std::unique_ptr<IttNode> lhs,
        std::unique_ptr<IttNode> rhs,
        IttBinaryOperation op,
        IttType resultType)
        : IttNode(resultType), _lhs(std::move(lhs)), _rhs(std::move(rhs)), _op(op) {}

    const IttNode& getLhs() const { return *_lhs; }
    const IttNode& getRhs() const { return *_rhs; }
    IttBinaryOperation getOperation() const { return _op; }

    void accept(IttVisitor& visitor) override;
};

class IttVariableNode : public IttNode {
    std::string _name;

  public:
    IttVariableNode(const std::string& name, IttType type)
        : IttNode(type), _name(name) {}

    const std::string& getName() const { return _name; }

    void accept(IttVisitor& visitor) override;
};

class IttFunctionNode : public IttNode {
    std::string _name;
    std::vector<std::pair<std::string, IttType>> _parameters;
    std::unique_ptr<IttNode> _body;

  public:
    IttFunctionNode(
        const std::string& name,
        std::vector<std::pair<std::string, IttType>> parameters,
        std::unique_ptr<IttNode> body,
        IttType returnType)
        : IttNode(returnType), _name(name), _parameters(std::move(parameters)), _body(std::move(body)) {}

    const std::string& getName() const { return _name; }
    const std::vector<std::pair<std::string, IttType>>& getParameters() const { return _parameters; }
    const IttNode& getBody() const { return *_body; }

    void accept(IttVisitor& visitor) override;
};

class IttBlockNode : public IttNode {
    std::vector<std::unique_ptr<IttNode>> _statements;

  public:
    IttBlockNode(std::vector<std::unique_ptr<IttNode>> statements)
        : IttNode(IttType(IttType::VOID)), _statements(std::move(statements)) {}

    const std::vector<std::unique_ptr<IttNode>>& getStatements() const { return _statements; }

    void accept(IttVisitor& visitor) override;
};
