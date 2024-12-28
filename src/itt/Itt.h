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
    virtual void visit(class IttBinaryOperationNode& node) = 0;
    virtual void visit(class IttVariableNode& node) = 0;
    virtual void visit(class IttFunctionNode& node) = 0;
    virtual void visit(class IttBlockNode& node) = 0;
    virtual void visit(class IttIntegerNode& node) = 0;
    virtual void visit(class IttFloatNode& node) = 0;
    virtual void visit(class IttBooleanNode& node) = 0;
    virtual void visit(class IttCharNode& node) = 0;
    virtual void visit(class IttReturnNode& node) = 0;
};

enum class IttVisibility {
    EXTERN,
    PUBLIC,
    PRIVATE
};

class IttIntegerNode : public IttNode {
  int _value;

  public:
    IttIntegerNode(int value) : IttNode(IttType(IttType::INT)), _value(value) {}

    int getValue() const { return _value; }

    void accept(IttVisitor& visitor) override { visitor.visit(*this); }
};

class IttFloatNode : public IttNode {
  float _value;

  public:
  IttFloatNode(float value): IttNode(IttType(IttType::FLOAT)), _value(value) {}

  float getValue() const { return _value; }

  void accept(IttVisitor& visitor) override;
};

class IttBooleanNode : public IttNode {
  bool _value;

  public:
  IttBooleanNode(bool value): IttNode(IttType(IttType::BOOL)), _value(value) {}

  bool getValue() const { return _value; }

  void accept(IttVisitor& visitor) override { visitor.visit(*this); }
};

class IttCharNode : public IttNode {
  char _value;

  public:
  IttCharNode(char value): IttNode(IttType(IttType::CHAR)), _value(value) {}

  char getValue() const { return _value; }

  void accept(IttVisitor& visitor) override { visitor.visit(*this); }
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

    IttNode& getLhs() const { return *_lhs; }
    IttNode& getRhs() const { return *_rhs; }
    IttBinaryOperation getOperation() const { return _op; }

    void accept(IttVisitor& visitor) override { visitor.visit(*this); }
};

class IttVariableNode : public IttNode {
    std::string _name;
    std::unique_ptr<IttNode> _attachedContent;
  public:
    IttVariableNode(const std::string& name, IttType type, std::unique_ptr<IttNode> attached)
        : IttNode(type), _name(name), _attachedContent(std::move(attached)) {}

    const std::string& getName() const { return _name; }

    IttNode& getContent() const { return *_attachedContent; }

    void accept(IttVisitor& visitor) override { visitor.visit(*this); }
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
    IttNode& getBody() const { return *_body; }

    void accept(IttVisitor& visitor) override { visitor.visit(*this); }
};

class IttBlockNode : public IttNode {
    std::vector<std::unique_ptr<IttNode>> _statements;

  public:
    IttBlockNode(std::vector<std::unique_ptr<IttNode>> statements)
        : IttNode(IttType(IttType::UNRESOLVED)), _statements(std::move(statements)) {}

    const std::vector<std::unique_ptr<IttNode>>& getStatements() const { return _statements; }

    void accept(IttVisitor& visitor) override { visitor.visit(*this); }
};

class IttReturnNode : public IttNode {
  std::optional<std::unique_ptr<IttNode>> _attachedContent;

  public: 
  IttReturnNode(std::optional<std::unique_ptr<IttNode>> attached) : IttNode(IttType(IttType::UNRESOLVED)), _attachedContent(std::move(attached)) {}

  const std::optional<std::unique_ptr<IttNode>>& getReturnStmt() const { return _attachedContent; }

  void accept(IttVisitor& visitor) override { visitor.visit(*this); }
};