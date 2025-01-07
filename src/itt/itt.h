#pragma once
#include <memory>
#include <vector>
#include<optional>

#include "itt_type.h"

class IttNode {
  protected:
    IttType _type;

  public:
    explicit IttNode() : _type(IttType::UNRESOLVED) {}
    virtual ~IttNode() = default;

    IttType getType() const { return _type; }
    void setType(IttType type) { this->_type = type; }

    virtual void accept(class IttVisitor& visitor) = 0;
    virtual bool operator==(const IttNode& other) const = 0;
};

class IttVisitor {
  public:
    virtual void visit(class IttBinaryOperationNode& node) = 0;
    virtual void visit(class IttVariableNode& node) = 0;
    virtual void visit(class IttFunctionNode& node) = 0;
    virtual void visit(class IttBlockNode& node) = 0;
    virtual void visit(class IttIntegerNode& node) = 0;
    virtual void visit(class IttIdentifierNode& node) = 0;
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
    IttIntegerNode(int value) : IttNode(), _value(value) {}

    int getValue() const { return _value; }

    void accept(IttVisitor& visitor) override { visitor.visit(*this); }

    bool operator==(const IttNode& other) const override {
        if (const IttIntegerNode* otherIntNode = dynamic_cast<const IttIntegerNode*>(&other)) {
            return this->_value == otherIntNode->_value;
        }
        return false;
    }
};


class IttIdentifierNode : public IttNode {
  std::string _name;
public:
  IttIdentifierNode(std::string name): IttNode(), _name(name) {}

  std::string getName() const { return _name; }

  void accept(IttVisitor& visitor) override { visitor.visit(*this); }

  bool operator==(const IttNode& other) const override {
      if (const IttIdentifierNode* otherIdNode = dynamic_cast<const IttIdentifierNode*>(&other)) {
          return this->_name == otherIdNode->_name;
      }
      return false;
  }
};


class IttFloatNode : public IttNode {
  float _value;

  public:
  IttFloatNode(float value): IttNode(), _value(value) {}

  float getValue() const { return _value; }

  void accept(IttVisitor& visitor) override { visitor.visit(*this); };

  bool operator==(const IttNode& other) const override {
      if (const IttFloatNode* otherFloatNode = dynamic_cast<const IttFloatNode*>(&other)) {
          return this->_value == otherFloatNode->_value;
      }
      return false;
  }
};

class IttBooleanNode : public IttNode {
  bool _value;

  public:
  IttBooleanNode(bool value): IttNode(), _value(value) {}

  bool getValue() const { return _value; }

  void accept(IttVisitor& visitor) override { visitor.visit(*this); }

  bool operator==(const IttNode& other) const override {
      if (const IttBooleanNode* otherBoolNode = dynamic_cast<const IttBooleanNode*>(&other)) {
          return this->_value == otherBoolNode->_value;
      }
      return false;
  }
};

class IttCharNode : public IttNode {
  char _value;

  public:
  IttCharNode(char value): IttNode(), _value(value) {}

  char getValue() const { return _value; }

  void accept(IttVisitor& visitor) override { visitor.visit(*this); }

  bool operator==(const IttNode& other) const override {
      if (const IttCharNode* otherCharNode = dynamic_cast<const IttCharNode*>(&other)) {
          return this->_value == otherCharNode->_value;
      }
      return false;
  }
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
        IttBinaryOperation op)
        : IttNode(), _lhs(std::move(lhs)), _rhs(std::move(rhs)), _op(op) {}

    IttNode& getLhs() const { return *_lhs; }
    IttNode& getRhs() const { return *_rhs; }
    IttBinaryOperation getOperation() const { return _op; }

    void accept(IttVisitor& visitor) override { visitor.visit(*this); }

    bool operator==(const IttNode& other) const override {
        if (const IttBinaryOperationNode* otherOpNode = dynamic_cast<const IttBinaryOperationNode*>(&other)) {
            return this->_op == otherOpNode->_op &&
                  *this->_lhs == *otherOpNode->_lhs &&
                  *this->_rhs == *otherOpNode->_rhs;
        }
        return false;
    }
};

class IttVariableNode : public IttNode {
    std::string _name;
    std::unique_ptr<IttNode> _attachedContent;
  public:
    IttVariableNode(const std::string& name, std::unique_ptr<IttNode> attached)
        : IttNode(), _name(name), _attachedContent(std::move(attached)) {}

    const std::string& getName() const { return _name; }

    IttNode& getContent() const { return *_attachedContent; }

    void accept(IttVisitor& visitor) override { visitor.visit(*this); }

    bool operator==(const IttNode& other) const override {
        if (const IttVariableNode* otherVarNode = dynamic_cast<const IttVariableNode*>(&other)) {
            return this->_name == otherVarNode->_name && *this->_attachedContent == *otherVarNode->_attachedContent;
        }
        return false;
    }
};

class IttFunctionNode : public IttNode {
    std::string _name;
    std::vector<std::pair<std::string, IttType>> _parameters;
    std::unique_ptr<IttNode> _body;

  public:
    IttFunctionNode(
        const std::string& name,
        std::vector<std::pair<std::string, IttType>> parameters,
        std::unique_ptr<IttNode> body)
        : IttNode(), _name(name), _parameters(std::move(parameters)), _body(std::move(body)) {}

    const std::string& getName() const { return _name; }
    const std::vector<std::pair<std::string, IttType>>& getParameters() const { return _parameters; }
    IttNode& getBody() const { return *_body; }

    void accept(IttVisitor& visitor) override { visitor.visit(*this); }

    bool operator==(const IttNode& other) const override {
        if (const IttFunctionNode* otherFuncNode = dynamic_cast<const IttFunctionNode*>(&other)) {
            return this->_name == otherFuncNode->_name &&
                    this->_parameters == otherFuncNode->_parameters &&
                    *this->_body == *otherFuncNode->_body;
        }
        return false;
    }
};

class IttBlockNode : public IttNode {
    std::vector<std::unique_ptr<IttNode>> _statements;

  public:
    IttBlockNode(std::vector<std::unique_ptr<IttNode>>&& statements)
        : IttNode(), _statements(std::move(statements)) {}

    std::vector<std::unique_ptr<IttNode>>&& getStatements() {
        return std::move(_statements);
    }


    void accept(IttVisitor& visitor) override { visitor.visit(*this); }

  bool operator==(const IttNode& other) const override {
      if (const IttBlockNode* otherBlockNode = dynamic_cast<const IttBlockNode*>(&other)) {
          if (_statements.size() != otherBlockNode->_statements.size()) return false;
          for (size_t i = 0; i < _statements.size(); ++i) {
              if (!(*_statements[i] == *otherBlockNode->_statements[i])) return false;
          }
          return true;
      }
      return false;
  }
};

class IttReturnNode : public IttNode {
  std::optional<std::unique_ptr<IttNode>> _attachedContent;

  public: 
  IttReturnNode(std::optional<std::unique_ptr<IttNode>> attached) : IttNode(), _attachedContent(std::move(attached)) {}

  const std::optional<std::unique_ptr<IttNode>>& getReturnStmt() const { return _attachedContent; }

  void accept(IttVisitor& visitor) override { visitor.visit(*this); }

  bool operator==(const IttNode& other) const override {
      if (const IttReturnNode* otherReturnNode = dynamic_cast<const IttReturnNode*>(&other)) {
          if (this->_attachedContent && otherReturnNode->_attachedContent) {
              return *this->_attachedContent == *otherReturnNode->_attachedContent;
          }
          return !this->_attachedContent && !otherReturnNode->_attachedContent;
      }
      return false;
  }
};